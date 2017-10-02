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

	ecs::Entity *leftPaddle, *rightPaddle, *ballEntity;
	ecs::Entity *cpuPaddle;

	ecs::BoxCollider2D *left, *right, *ball;

	float ball_x_change, ball_y_change;
	const float BALL_SPEED = 5.0f;

	const int WIDTH = 800;
	const int HEIGHT = 600;

public:
	Game()
	{
		sudo.init(math::Vector2(WIDTH, HEIGHT), "Pong!", this);
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
		leftPaddle->AddComponent(new ecs::RectangleComponent(math::Vector2(10, 100), math::Vector4(1, 0, 0, 1)));
		leftPaddle->AddComponent(new ecs::BoxCollider2D());
		leftPaddle->GetComponent<ecs::BoxCollider2D>()->SetKeepInBounds(true);
		left = leftPaddle->GetComponent<ecs::BoxCollider2D>();

		// Right Paddle
		rightPaddle = new ecs::Entity("rightPaddle");
		rightPaddle->transform->position = math::Vector3(800 - 25 - 30, 0, 0);
		rightPaddle->AddComponent(new PaddleComponent("up", "down"));
		rightPaddle->AddComponent(new ecs::RectangleComponent(math::Vector2(10, 100), math::Vector4(0, 1, 1, 1)));
		rightPaddle->AddComponent(new ecs::BoxCollider2D());
		rightPaddle->GetComponent<ecs::BoxCollider2D>()->SetKeepInBounds(true);
		right = rightPaddle->GetComponent<ecs::BoxCollider2D>();

		// Ball
		ballEntity = new ecs::Entity("ball");
		ballEntity->AddComponent(new ecs::RectangleComponent(math::Vector2(20, 20), math::Vector4(1, 1, 0, 1)));
		ballEntity->transform->position = math::Vector3((800 / 2) - 10, 10, 0);
		ballEntity->AddComponent(new ecs::BoxCollider2D());
		ball = ballEntity->GetComponent<ecs::BoxCollider2D>();

		ball_x_change = BALL_SPEED;
		ball_y_change = BALL_SPEED;
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
			// input for stuff
			if (input->GetKeyDown("escape")) {
				state = GameStates::MENU;
				this->ResetAfterGame();
			}

			// Ball Logic
			this->BallLogic();

			// Draw stuff
			renderer->Draw(leftPaddle->GetComponent<ecs::RectangleComponent>());
			renderer->Draw(rightPaddle->GetComponent<ecs::RectangleComponent>());			
			renderer->Draw(ballEntity->GetComponent<ecs::RectangleComponent>());
		}
	}

	void ResetAfterGame() 
	{
		rightPaddle->transform->position = math::Vector3(800 - 25 - 30, 0, 0);
		leftPaddle->transform->position = math::Vector3(30, 0, 0);
	}

	void BallLogic() 
	{
		ballEntity->transform->Move(math::Vector3(ball_x_change, ball_y_change, 0));

		// Ball to paddle 
		if (ball->Intersects(*right) || ball->Intersects(*left)) {
			// Make the ball bounce
			ball_x_change *= -1;

			// Shake window
			input->WindowShake(30, 4);

			// Change background color
			srand(time(NULL));
			config->SetBackgroundColor(math::Vector4(rand() & 1 + 1, rand() & 1 + 1, rand() & 1 + 1, 0));
		}

		// Vertical walls collision
		if (ballEntity->transform->position.getY() <= 0) {
			ball_y_change *= -1;
		}
		if (ballEntity->transform->position.getY() + 20 > HEIGHT) {
			ball_y_change *= -1;
		}
	}
};

int main()
{
	Game* game = new Game();

	return 0;
}