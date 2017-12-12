#include"../../sudo.h"

using namespace sudo;

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 700

class PlayerMove : public ecs::Component {
private:
	sudo_system::InputSystem *input = sudo_system::InputSystem::Instance();
	ecs::Transform *transform;
	float angleVelocity;
	const float maxAngleVelocity = 0.01f;
	const float maxVelocity = 0.1f;

public:
	void Start() override {
		transform = m_entityHolder->transform;
	}

	void Update(float deltaTime) override {
		// Angular velocity and cool gameplay stuff
		if (input->GetKey("right")) {
			angleVelocity += 0.000005f;
		}
		else if (input->GetKey("left")) {
			angleVelocity -= 0.000005f;
		}
		else {
			if (angleVelocity > 0) {
				angleVelocity -= 0.000005f;
			}
			if (angleVelocity < 0) {
				angleVelocity += 0.000005f;
			}
		}
		transform->angle += ( angleVelocity * deltaTime );

		// trigonometry takes input in radians
		// Moving forward and cool stuff
		if (input->GetKey("up")) {
			transform->position = math::Vector3(transform->position.x + (maxVelocity * sin(transform->angle+1.57) * deltaTime), transform->position.y + (maxVelocity * cos(transform->angle+1.57) * deltaTime), 0);
		}

		/*
		moveForward(float angle)
		{
		x += speed * sin(angle);
		y += speed * cos(angle);
		}
		*/
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
	// MyGame methods
	void MenuUpdate(float deltaTime);
	void PlayingUpdate(float deltaTime);

private:
	// Entities
	ecs::Entity *backgroundEntity;
	ecs::Entity *player;
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

void MyGame::MenuUpdate(float deltaTime)
{
	// Render
	renderer->Submit(backgroundEntity->GetComponent<ecs::SpriteComponent>());

	// Look for input to start game
	if (input->GetKey("x")) {
		state = GameState::PLAYING;
	}
}

void MyGame::PlayingUpdate(float deltaTime) 
{
	renderer->Submit(player->GetComponent<ecs::RectangleComponent>());
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