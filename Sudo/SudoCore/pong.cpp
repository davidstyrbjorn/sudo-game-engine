#include"core\sudo.h"

using namespace sudo;

// User end componet
class PaddleComponent : public ecs::Component {
private:
	char *upKey, *downKey;
	sudo_system::InputSystem *input;

	const float SPEED = 0.8f;

public:
	PaddleComponent(char* _upKey, char* _downKey) 
	{
		upKey = _upKey;
		downKey = _downKey;
		
		input = sudo_system::InputSystem::Instance();
	}

	~PaddleComponent() {

	}

	void Update(float deltaTime) override {
		if (input->GetKey(upKey)) {
			m_entityHolder->transform->Move(math::Vector3(0, -SPEED * deltaTime, 0));
		}
		if (input->GetKey(downKey)) {
			m_entityHolder->transform->Move(math::Vector3(0, SPEED * deltaTime, 0));
		}
	}

	void Start () override { }
};

// ====================================================== //
// ====================================================== //

class Game : SudoClass {
private:
	SudoCore sudo;

	enum GameStates { MENU, PLAYING };
	GameStates state;

	ecs::Entity *backgroundMenu, *backgroundGame;

	ecs::Entity *leftPaddle, *rightPaddle, *ballEntity;
	ecs::Entity *cpuPaddle;

	ecs::BoxCollider2D *left, *right, *ball;

	float ball_x_change, ball_y_change;
	const float BALL_SPEED = 0.5f;

	const int WIDTH = 800;
	const int HEIGHT = 600;
	const float SPEED_INCREASE = 0.05f;

	int leftScore = 0, rightScore = 0;
	utility::Timer gameClock;

public:
	Game()
	{
		sudo.init(math::Vector2(WIDTH, HEIGHT), "Pong!", this);
	}

	void Start()
	{
		state = GameStates::MENU;

		backgroundMenu = new ecs::Entity("backgroundMenu");
		backgroundMenu->AddComponent(new ecs::SpriteComponent("C:\\SudoGameEngine\\images\\_pong_assets\\title_screen_texture.png"));
		
		backgroundGame = new ecs::Entity("backgroundGame");
		backgroundGame->AddComponent(new ecs::SpriteComponent("C:\\SudoGameEngine\\images\\_pong_assets\\game_background.jpg"));

		// Left Paddle
		leftPaddle = new ecs::Entity("leftPaddle");
		leftPaddle->transform->position = math::Vector3(30, 0, 0);
		leftPaddle->AddComponent(new PaddleComponent("w", "s"));
		leftPaddle->AddComponent(new ecs::SpriteComponent("C:\\SudoGameEngine\\images\\_pong_assets\\paddle.png"));
		leftPaddle->AddComponent(new ecs::BoxCollider2D());
		leftPaddle->GetComponent<ecs::BoxCollider2D>()->SetKeepInBounds(true);
		left = leftPaddle->GetComponent<ecs::BoxCollider2D>();

		// Right Paddle
		rightPaddle = new ecs::Entity("rightPaddle");
		rightPaddle->transform->position = math::Vector3(800 - 25 - 30, 0, 0);
		rightPaddle->AddComponent(new PaddleComponent("up", "down"));
		rightPaddle->AddComponent(new ecs::SpriteComponent("C:\\SudoGameEngine\\images\\_pong_assets\\paddle.png"));
		rightPaddle->AddComponent(new ecs::BoxCollider2D());
		rightPaddle->GetComponent<ecs::BoxCollider2D>()->SetKeepInBounds(true);
		right = rightPaddle->GetComponent<ecs::BoxCollider2D>();

		// Ball
		ballEntity = new ecs::Entity("ball");
		ballEntity->AddComponent(new ecs::SpriteComponent("C:\\SudoGameEngine\\images\\_pong_assets\\test.jpg"));
		ballEntity->transform->position = math::Vector3((800 / 2) - 10, (600/2) - 10, 0);
		ballEntity->AddComponent(new ecs::BoxCollider2D());
		ball = ballEntity->GetComponent<ecs::BoxCollider2D>();

		ball_x_change = BALL_SPEED;
		ball_y_change = BALL_SPEED;

		config->SetFPS(60);
	}

	void Update(float deltaTime)
	{
		if (state == GameStates::MENU) 
		{
			// Input for start
			if (input->GetKeyDown("x")) {
				this->StartGame();
			}

			// Draw stuff
			renderer->Submit(backgroundMenu->GetComponent<ecs::SpriteComponent>());
		}
		else if (state == GameStates::PLAYING)
		{
			// input for stuff
			if (input->GetKeyDown("escape")) {
				state = GameStates::MENU;
				this->ResetAfterGame();
			}

			// Ball Logic
			this->BallLogic(deltaTime);

			// Draw stuff
			renderer->Submit(backgroundGame->GetComponent<ecs::SpriteComponent>());
			renderer->Submit(leftPaddle->GetComponent<ecs::SpriteComponent>());
			renderer->Submit(rightPaddle->GetComponent<ecs::SpriteComponent>());			
			renderer->Submit(ballEntity->GetComponent<ecs::SpriteComponent>());
		}
	}

	void ResetAfterGame() 
	{
		gameClock.Stop();

		rightPaddle->transform->position = math::Vector3(800 - 25 - 30, 0, 0);
		leftPaddle->transform->position = math::Vector3(30, 0, 0);

		leftScore = 0;
		rightScore = 0;

		ball_x_change = BALL_SPEED;
		ball_y_change = BALL_SPEED;
	}

	void StartGame()
	{
		state = GameStates::PLAYING;

		// Reset and start game clock
		gameClock.Reset();
		gameClock.Start();

		// Ball Position
		ballEntity->transform->position = math::Vector3((800 / 2) - 10, (600 / 2) - 10, 0);
	}

	void BallLogic(float deltaTime) 
	{
		if(gameClock.GetTicks() >= 1000)
			ballEntity->transform->Move(math::Vector3(ball_x_change * deltaTime, ball_y_change * deltaTime, 0));

		// Ball to paddle 
		if (ball->Intersects(*right)) {
			BallPaddleCollision("right");
		}
		if (ball->Intersects(*left)) {
			BallPaddleCollision("left");
		}

		// Vertical walls collision
		if (ballEntity->transform->position.y <= 0) {
			ball_y_change *= -1;
		}
		if (ballEntity->transform->position.y + 32 > HEIGHT) {
			ball_y_change *= -1;
		}

		// Horizontal wall out of bounds
		if (ballEntity->transform->position.x > WIDTH) {
			// Left Score
			leftScore++;

			// Reset game clock and ball position
			gameClock.Reset();
			ballEntity->transform->position = math::Vector3((800 / 2) - 10, (600 / 2) - 10, 0);

			// Reset ball 
			ball_x_change = BALL_SPEED;
			ball_y_change = BALL_SPEED;

			// Score
			std::string temp = std::string("Left: ") + std::string(std::to_string(leftScore)) + std::string(" Right: " ) + std::string(std::to_string(rightScore));
			config->SetWindowCaption(temp.c_str());
		}
		if (ballEntity->transform->position.x < -10) {
			// Right Score
			rightScore++;

			// Reset game clock and ball position
			gameClock.Reset();
			ballEntity->transform->position = math::Vector3((800 / 2) - 10, (600 / 2) - 10, 0);

			// Reset ball 
			ball_x_change = BALL_SPEED;
			ball_y_change = BALL_SPEED;

			// Print score
			system("cls");
			std::cout << "<=== SCORE ===>" << std::endl;
			std::cout << "Left: " << leftScore << std::endl;
			std::cout << "Right: " << rightScore << std::endl;
		}

		if (leftScore == 5 || rightScore == 5) {
			state = GameStates::MENU;
			ResetAfterGame();
		}
	}

	void BallPaddleCollision(utility::SudoString paddle) 
	{
		// Shake window
		input->WindowShake(30, 4);

		// Make the ball bounce
		ball_x_change *= -1;

		if (paddle == "left") 
		{
			// Increase ball speed
			ball_x_change += SPEED_INCREASE;

			float distanceToMiddle = ((leftPaddle->transform->position.y+50) - (ballEntity->transform->position.y+10));
			ball_y_change += (distanceToMiddle/100)*-1;
		}
		if (paddle == "right") 
		{
			// Increase ball speed
			ball_x_change -= SPEED_INCREASE;

			float distanceToMiddle = ((rightPaddle->transform->position.y+50) - (ballEntity->transform->position.y+10));
			ball_y_change += (distanceToMiddle/200)*-1;
		}
	}
};

int main()
{
	Game* game = new Game();

	return 0;
}