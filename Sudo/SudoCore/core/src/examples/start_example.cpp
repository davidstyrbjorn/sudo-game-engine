// Master include file, includes all the engine .h files
#include"../../sudo.h"

// Core namespce used for all classes 
using namespace sudo;

// All the various system classes
using namespace sudo_system;

// Vector, matrices, color classes etc
using namespace math;

// Entity & component classes
using namespace ecs;

class MyGame : SudoClass {
public:
	// Engine object
	SudoCore* engine;

	// Constructor 
	MyGame();

	// Behaviour overrides
	void Update(float deltaTime) override;
	void Start() override;
	void OnApplicationQuit() override;

	// Game data
	Entity *player;
};

void MyGame::Start() 
{
	// Create the player entity
	player = new Entity("player");
	player->AddComponent(new RectangleComponent(Vector2(100, 100), Color(255, 255, 0, 255)));
}

void MyGame::Update(float deltaTime) 
{
	// Draw the player
	renderer->Submit(player->GetComponent<RectangleComponent>());
}

void MyGame::OnApplicationQuit()
{

}

MyGame::MyGame() 
{
	engine = new SudoCore();
	engine->init(Vector2(400, 400), "Sudo Game Engine", this);
}

int main() {
	MyGame *game = new MyGame();

	return EXIT_SUCCESS;
}