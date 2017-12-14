#include"../../sudo.h"
#include"asteroids_components.h"

using namespace sudo;

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 700

class PlayerMove : public ecs::Component {
private:
	sudo_system::InputSystem *input = sudo_system::InputSystem::Instance();
	ecs::Transform *transform;
	float angleVelocity, linearVelocity;
	const float maxAngleVelocity = 0.25f;
	const float maxVelocity = 0.35f;

public:
	void Start() override {
		transform = m_entityHolder->transform;
	}

	void Update(float deltaTime) override {
		// Angular velocity and cool gameplay stuff
		if (input->GetKey("right")) {
			angleVelocity = maxAngleVelocity;
		}
		else if (input->GetKey("left")) {
			angleVelocity = -maxAngleVelocity;
		}
		else {
			angleVelocity = 0;
		}
		transform->angle += (angleVelocity * deltaTime);

		// Moving forward and cool stuff
		if (input->GetKey("up")) {
			if (linearVelocity < maxVelocity) {
				linearVelocity += 0.0005f;
			}
		}
		else {
			if (linearVelocity > 0) {
				linearVelocity -= 0.00005f;
			}
			else {
				linearVelocity = 0;
			}
		}
		float angleInRadians = transform->angle * DEG2RAD;
		transform->position = math::Vector3(transform->position.x + (linearVelocity * -sin(angleInRadians) * deltaTime), transform->position.y + (linearVelocity * cos(angleInRadians) * deltaTime), 0);
	}
};

class Projectile : public ecs::Component {
private:
	ecs::Transform *transform;
	const float velocity = 0.5f;
	sudo_system::BatchRendererSystem *renderer = sudo_system::BatchRendererSystem::Instance();
	ecs::RectangleComponent *rectangleComponent;

public:
	void Start() override {
		transform = m_entityHolder->transform;
		rectangleComponent = m_entityHolder->GetComponent<ecs::RectangleComponent>();
	}

	void Update(float deltaTime) override {
		float angleInRadians = transform->angle * DEG2RAD;
		transform->position = math::Vector3(transform->position.x + (velocity * -sin(angleInRadians) * deltaTime), transform->position.y + (velocity * cos(angleInRadians) * deltaTime), 0);
	}

	void Render() override {
		if (transform->position.x < -5 || transform->position.x > WINDOW_WIDTH || transform->position.y < -5 || transform->position.y > WINDOW_HEIGHT) {
			m_entityHolder->Destroy();
		}
		else {
			renderer->Submit(rectangleComponent);
		}
	}
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

private:
	// Entities
	ecs::Entity *backgroundEntity;
	ecs::Entity *player;
	bool canShoot = true;
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
	player->AddComponent(new ecs::RectangleComponent(math::Vector2(10, 40), math::Color(255, 0, 155, 255)));
	player->transform->position = math::Vector3((WINDOW_WIDTH / 2) - 5, (WINDOW_HEIGHT / 2) - 20, 0);
	player->AddComponent(new PlayerMove());

	// Configurations
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
}

void MyGame::MenuUpdate(float deltaTime)
{
	// Look for input to start game
	if (input->GetKey("x")) {
		state = GameState::PLAYING;
	}
}

void MyGame::PlayingUpdate(float deltaTime) 
{
	if (input->GetKeyDown("space") && canShoot) {
		canShoot = false;

		ecs::Entity *temp = new ecs::Entity();
		temp->Start();
		temp->AddComponent(new ecs::RectangleComponent(math::Vector2(5, 5), math::Color::Red()))->Start();
		temp->AddComponent(new Projectile())->Start();

		temp->transform->position = player->transform->position;
		temp->transform->angle = player->transform->angle;
	}
	if (!input->GetKey("space"))
	{
		canShoot = true;	
	}
}

MyGame::MyGame()
{
	engine.init(math::Vector2(WINDOW_WIDTH, WINDOW_HEIGHT), "Asteroids", this);
}

int main()
{
	MyGame *game = new MyGame();

	return EXIT_SUCCESS;
}