#include"core\sudo.h"

using namespace sudo;

// User end componet
class PaddleComponent : public ecs::Component {
private:
	char *upKey, *downKey;
	system::InputSystem *input;

	const int SPEED = 10;

public:
	PaddleComponent(char* _upKey, char* _downKey) {
		m_componentName = "PaddleComponent";

		upKey = _upKey;
		downKey = _downKey;

		input = system::InputSystem::Instance();
	}

	~PaddleComponent() {

	}

	void Update() {
		if (input->GetKey(upKey)) {
			m_entityHolder->transform->Move(math::Vector3(0, -SPEED, 0));
		}
		if (input->GetKey(downKey)) {
			m_entityHolder->transform->Move(math::Vector3(0, SPEED, 0));
		}
	}

	void Start () { }
};

// ====================================================== //
// ====================================================== //

class Game : SudoClass {
private:
	SudoCore sudo;

	enum GameStates { MENU, PLAYING };
	GameStates state;

	ecs::Entity *backgroundMenu;

	ecs::Entity *leftPaddle, *rightPaddle;
	ecs::Entity *cpuPaddle;

public:
	Game()
	{
		sudo.init(math::Vector2(800, 600), "Pong!", this);
	}

	void Start()
	{
		state = GameStates::MENU;

		backgroundMenu = new ecs::Entity("backgroundMenu");
		backgroundMenu->AddComponent(new ecs::SpriteComponent("D:\\SudoGameEngine\\images\\_pong_assets\\title_screen_texture.png"));
		
		// Left Paddle
		leftPaddle = new ecs::Entity("leftPaddle");
		leftPaddle->transform->position = math::Vector3(30, 0, 0);
		leftPaddle->AddComponent(new PaddleComponent("w", "s"));
		leftPaddle->AddComponent(new ecs::RectangleComponent(math::Vector2(25, 100), math::Vector4(1, 0, 0, 1)));

		// Right Paddle
		rightPaddle = new ecs::Entity("rightPaddle");
		rightPaddle->transform->position = math::Vector3(800 - 25 - 30, 0, 0);
		rightPaddle->AddComponent(new PaddleComponent("up", "down"));
		rightPaddle->AddComponent(new ecs::RectangleComponent(math::Vector2(25, 100), math::Vector4(0, 1, 1, 1)));
	}

	void Update()
	{
		if (state == GameStates::MENU) 
		{
			// Input for start
			if (input->GetKeyDown("x"))
				state = GameStates::PLAYING;

			// Draw stuff
			renderer->Draw(backgroundMenu->GetComponent<ecs::SpriteComponent>());
		}
		else if (state == GameStates::PLAYING)
		{
			// Draw stuff
			renderer->Draw(leftPaddle->GetComponent<ecs::RectangleComponent>());
			renderer->Draw(rightPaddle->GetComponent<ecs::RectangleComponent>());
		}
	}
};

int main()
{
	Game* game = new Game();

	return 0;
}