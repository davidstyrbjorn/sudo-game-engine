#include"../../sudo.h"
#include"asteroids_components.h"

using namespace sudo;

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 700
#define ASTEROID_MAX_WIDTH 40
#define ASTEROID_MIN_WIDTH 60
#define ASTEROID_MAX_HEIGHT 60
#define ASTEROID_MIN_HEIGHT 40

#define PROJECTILE_SIZE 5 

enum ENTITY_ID {
	ASTEROID = 0x01,
	PROJECTILE = 0x02,
};

class MyGame : SudoClass {
public:
	SudoCore engine;

	enum GameState { MENU, PLAYING };
	GameState state;

	// Constructor 
	MyGame();

	// Behaviour overrides
	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;
	// MyGame methods
	void MenuUpdate(float deltaTime);
	void MenuDraw();
	void PlayingUpdate(float deltaTime);
	void PlayingDraw();

	void TookHit();
	void ResetGame();

public:
	// Entities
	ecs::Entity *backgroundEntity;
	ecs::Entity *player;
	ecs::BoxCollider2D *playerCollider;
	bool canShoot = true;
	utility::Timer *asteroidsTimer;
	float asteroidSpawnTime = 2500; // In milliseconds
	int extraLifes = 3;
};

class PlayerMove : public ecs::Component {
private:
	sudo_system::InputSystem *input = sudo_system::InputSystem::Instance();
	ecs::Transform *transform;
	float angleVelocity, linearVelocity;
	const float maxAngleVelocity = 0.4f;
	const float maxVelocity = 0.35f;

public:
	void Start() override {
		transform = m_entityHolder->transform;
	}

	void Update(float deltaTime) override {
		// Angular velocity and cool gameplay stuff
		if (input->GetKey("left")) {
			angleVelocity = -maxAngleVelocity;
		}
		else if (input->GetKey("right")) {
			angleVelocity = maxAngleVelocity;
		}
		else {
			angleVelocity = 0;
		}
		transform->angle += (angleVelocity * deltaTime);

		// Moving forward and cool stuff
		if (input->GetKey("up")) {
			if (linearVelocity < maxVelocity) {
				linearVelocity += 0.05f * deltaTime;
			}
		}
		else {
			if (linearVelocity > 0) {
				linearVelocity -= 0.0005f * deltaTime;
			}
			else {
				linearVelocity = 0;
			}
		}
		float angleInRadians = transform->angle * DEG2RAD;
		transform->position = math::Vector3(transform->position.x + (linearVelocity * -sin(angleInRadians) * deltaTime), transform->position.y + (linearVelocity * cos(angleInRadians) * deltaTime), 0);
	}
};

class Projectile : public ecs::Component
{
private:
	ecs::Transform *transform;
	ecs::RectangleComponent *rectangleComponent;
	sudo_system::BatchRendererSystem *renderer = sudo_system::BatchRendererSystem::Instance();
	float angle;
	float xDirection, yDirection;
	const float velocity = 0.8f;

public:
	Projectile(float angle)
	{
		this->angle = angle * DEG2RAD;
		xDirection = velocity * ( -sin(this->angle));
		yDirection = velocity * (  cos(this->angle));
	}

	void Start() override 
	{
		transform = m_entityHolder->transform;
		rectangleComponent = m_entityHolder->GetComponent<ecs::RectangleComponent>();
	}

	void Update(float deltaTime) override
	{
		transform->Move(math::Vector3(xDirection, yDirection, 0) * deltaTime);

		// OOB
		if (transform->position.x > WINDOW_WIDTH) {
			m_entityHolder->Destroy();
		}
		else if (transform->position.x < -PROJECTILE_SIZE) {
			m_entityHolder->Destroy();
		}
		else if (transform->position.y > WINDOW_HEIGHT) {
			m_entityHolder->Destroy();
		}
		else if (transform->position.y < -PROJECTILE_SIZE) {
			m_entityHolder->Destroy();
		}
	}

	void Render() override
	{
		renderer->Submit(rectangleComponent);
	}
};

class Asteroid : public ecs::Component
{
private:
	ecs::Transform *transform;
	sudo_system::BatchRendererSystem *renderer = sudo_system::BatchRendererSystem::Instance();
	sudo_system::SettingsSystem *config = sudo_system::SettingsSystem::Instance();
	sudo_system::WorldSystem *world = sudo_system::WorldSystem::Instance();
	ecs::RectangleComponent *rectangleComponent;
	ecs::BoxCollider2D *thisCollider, *playerCollider;

	std::vector<ecs::BoxCollider2D*> projectileList;

	float randomAngularVelocity;
	math::Vector3 moveDirection;
	float moveSpeed;
	const char* side;

public:
	Asteroid(float _x, float _y, const char* _side, ecs::BoxCollider2D *a_playerCollider)
	{
		moveDirection = math::Vector3(_x, _y, 0);
		side = _side;
		playerCollider = a_playerCollider;
	}

	void Start() override
	{
		float maxAngleVelocity = 0.25f;
		randomAngularVelocity = utility::SudoRandomNumber::GetRandomFloatingPoint(-maxAngleVelocity, maxAngleVelocity);

		transform = m_entityHolder->transform;

		rectangleComponent = (ecs::RectangleComponent*)(m_entityHolder->GetRenderableComponent());
		thisCollider = m_entityHolder->GetComponent<ecs::BoxCollider2D>();
	}						

	void Update(float deltaTime) override
	{
		// Move the asteroid
		transform->Rotate(randomAngularVelocity * deltaTime);
		transform->Move(moveDirection * deltaTime);

		// Check for collision with player
		if (thisCollider->Intersects(*playerCollider)) {
			m_entityHolder->Destroy();
			static_cast<MyGame*>(config->instancePtr)->TookHit();
			return;
		}

		// See if the asteroid is out of bounds
		if (transform->position.x > WINDOW_WIDTH && side != "right") {
			m_entityHolder->Destroy();
		}
		else if (transform->position.x < -ASTEROID_MAX_WIDTH && side != "left") {
			m_entityHolder->Destroy();
		}
		else if (transform->position.y > WINDOW_HEIGHT && side != "bottom") {
			m_entityHolder->Destroy();
		}
		else if (transform->position.y < -ASTEROID_MAX_HEIGHT && side != "top") {
			m_entityHolder->Destroy();
		}
	}

	void Render() override
	{
		projectileList.clear();
		std::vector<ecs::Entity*> temp = world->GetEntitiesWithID(ENTITY_ID::PROJECTILE);
		for (int i = 0; i < temp.size(); i++) {
			if (thisCollider->Intersects(*temp[i]->GetComponent<ecs::BoxCollider2D>())) {
				m_entityHolder->Destroy();
				temp[i]->Destroy();
			}
		}
		renderer->Submit(rectangleComponent);
	}
};

void MyGame::Start()
{
	// Initial game state 
	state = GameState::MENU;

	// Creating entities
	backgroundEntity = new ecs::Entity();
	backgroundEntity->AddComponent(new ecs::SpriteComponent("D:\\SudoGameEngine\\images\\_asteroids_assets\\menu_image.png"));

	// Player
	player = new ecs::Entity();
	player->AddComponent(new ecs::BoxCollider2D());
	playerCollider = player->GetComponent<ecs::BoxCollider2D>();
	player->AddComponent(new ecs::RectangleComponent(math::Vector2(10, 40), math::Color(255, 0, 155, 255)));
	player->transform->position = math::Vector3((WINDOW_WIDTH / 2) - 5, (WINDOW_HEIGHT / 2) - 20, 0);
	player->AddComponent(new PlayerMove());

	// Asteroids timer for spawning timer
	asteroidsTimer = new utility::Timer();
	asteroidsTimer->Start();

	// Configurations
	textRenderer->LoadFont("C:\\Windows\\Fonts\\arial.ttf", "arial", 40);
	textRenderer->SetFont("arial");
	config->SetFPS(60);
	config->SetBackgroundColor(math::Color(20, 20, 20, 255));
}

void MyGame::Update(float deltaTime)
{
	switch (state) {
	case GameState::MENU:
		MenuUpdate(deltaTime);
		break;
	case GameState::PLAYING:
		PlayingUpdate(deltaTime);
		break;
	}
}

void MyGame::Render() 
{
	switch (state) {
	case GameState::MENU:
		MenuDraw();
		break;
	case GameState::PLAYING:
		PlayingDraw();
		break;
	}
}

void MyGame::MenuDraw()
{
	renderer->Submit(backgroundEntity->GetComponent<ecs::SpriteComponent>());
}

void MyGame::PlayingDraw()
{
	renderer->Submit(player->GetComponent<ecs::RectangleComponent>());
	textRenderer->DrawText("Life " + std::to_string(extraLifes), math::Vector2(0, 0), math::Color(10, 120, 79));
}

void MyGame::MenuUpdate(float deltaTime)
{
	// Look for input to start game
	if (input->GetKey("x")) {
		ResetGame();
		state = GameState::PLAYING;
	}
} 

void MyGame::PlayingUpdate(float deltaTime) 
{
	if (input->GetKey("space") && canShoot) {
		canShoot = false;
		ecs::Entity* temp = new ecs::Entity(ENTITY_ID::PROJECTILE);
		temp->Start();
		temp->AddComponent(new ecs::RectangleComponent(math::Vector2(PROJECTILE_SIZE, PROJECTILE_SIZE), math::Color::Red()))->Start();
		temp->AddComponent(new Projectile(player->transform->angle))->Start();
		temp->transform->position = player->transform->position;
		temp->AddComponent(new ecs::BoxCollider2D())->Start();	
	}
	else if (!input->GetKey("space")) {
		canShoot = true;
	}

	// Spawning asteroids
	if (asteroidsTimer->GetTicks() >= asteroidSpawnTime) {
		if(asteroidSpawnTime > 600)
			asteroidSpawnTime -= 400;
		int spawnCount = utility::SudoRandomNumber::GetRandomInteger(1, 4);
		for (int i = 0; i < spawnCount; i++) {
			int side = utility::SudoRandomNumber::GetRandomInteger(0, 100);
			if (side < 25) {
				// Left
				ecs::Entity *asteroid = new ecs::Entity(ENTITY_ID::ASTEROID);
				asteroid->Start();
				asteroid->transform->position = math::Vector3(-ASTEROID_MAX_WIDTH, utility::SudoRandomNumber::GetRandomInteger(0, WINDOW_HEIGHT), 0);
				asteroid->AddComponent(new ecs::RectangleComponent(math::Vector2(ASTEROID_MAX_WIDTH, ASTEROID_MAX_WIDTH), math::Color::Green()))->Start();
				asteroid->AddComponent(new ecs::BoxCollider2D())->Start();
				asteroid->AddComponent(new Asteroid(utility::SudoRandomNumber::GetRandomFloatingPoint(0.1f, 0.5f), 0, "left", playerCollider))->Start();
			}
			else if (side < 50) {
				// Right
				ecs::Entity *asteroid = new ecs::Entity(ENTITY_ID::ASTEROID);
				asteroid->Start();
				asteroid->transform->position = math::Vector3(WINDOW_WIDTH + ASTEROID_MAX_WIDTH, utility::SudoRandomNumber::GetRandomInteger(0, WINDOW_HEIGHT), 0);
				asteroid->AddComponent(new ecs::RectangleComponent(math::Vector2(ASTEROID_MAX_WIDTH, ASTEROID_MAX_WIDTH), math::Color::Green()))->Start();
				asteroid->AddComponent(new ecs::BoxCollider2D())->Start();
				asteroid->AddComponent(new Asteroid(utility::SudoRandomNumber::GetRandomFloatingPoint(-0.5f, -0.1f), 0, "right", playerCollider))->Start();
			}
			else if (side < 75) {
				// Top
				ecs::Entity *asteroid = new ecs::Entity(ENTITY_ID::ASTEROID);
				asteroid->Start();
				asteroid->transform->position = math::Vector3(utility::SudoRandomNumber::GetRandomInteger(0, WINDOW_WIDTH), -ASTEROID_MAX_HEIGHT, 0);
				asteroid->AddComponent(new ecs::RectangleComponent(math::Vector2(ASTEROID_MAX_WIDTH, ASTEROID_MAX_WIDTH), math::Color::Green()))->Start();
				asteroid->AddComponent(new ecs::BoxCollider2D())->Start();
				asteroid->AddComponent(new Asteroid(0, utility::SudoRandomNumber::GetRandomFloatingPoint(0.1f, 0.5f), "top", playerCollider))->Start();
			}
			else {
				// Bottom
				ecs::Entity *asteroid = new ecs::Entity(ENTITY_ID::ASTEROID);
				asteroid->Start();
				asteroid->transform->position = math::Vector3(utility::SudoRandomNumber::GetRandomInteger(0, WINDOW_WIDTH), WINDOW_HEIGHT+ASTEROID_MAX_HEIGHT, 0);
				asteroid->AddComponent(new ecs::RectangleComponent(math::Vector2(ASTEROID_MAX_WIDTH, ASTEROID_MAX_WIDTH), math::Color::Green()))->Start();
				asteroid->AddComponent(new ecs::BoxCollider2D())->Start();
				asteroid->AddComponent(new Asteroid(0, utility::SudoRandomNumber::GetRandomFloatingPoint(-0.5f, -0.1f), "bottom", playerCollider))->Start();
			}
		}

		asteroidsTimer->Reset();
	}

	if (input->GetKey("f"))
	{
		// wow! 12/18/2017
		//std::vector<ecs::Entity*> temp = world->GetEntitiesWithID(ENTITY_ID::ASTEROID);		
		// wow! 12/18/2017
		// world->RemoveAllEntitiesWithID(ENTITY_ID::ASTEROID);
	}
}

void MyGame::TookHit()
{
	extraLifes--;
	input->WindowShake(350, 5);
	if (extraLifes <= 0)
		state = GameState::MENU;
}

void MyGame::ResetGame()
{
	asteroidSpawnTime = 2500;
	extraLifes = 3;
	player->transform->position = math::Vector3((WINDOW_WIDTH / 2) - 5, (WINDOW_HEIGHT / 2) - 20, 0);
	world->RemoveAllEntitiesWithID(ENTITY_ID::ASTEROID);
}

MyGame::MyGame()
{
	engine.init(math::Vector2(WINDOW_WIDTH, WINDOW_HEIGHT), "ASSteroids", this);
}

int main()
{
	MyGame *game = new MyGame();

	return EXIT_SUCCESS;
}