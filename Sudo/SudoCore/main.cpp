#include<iostream>
#include"core\sudo.h"

using namespace sudo;

/* Sandbox for testing implemented features */
class App : SudoClass {

private:
	SudoCore *coreEngine;
	system::InputSystem *input = system::InputSystem::Instance();
	system::RenderSystem *renderer = system::RenderSystem::Instance();
	system::SettingsSystem *settings = system::SettingsSystem::Instance();

	ecs::Entity *leftPaddle, *rightPaddle;
	
public:
	App() 
	{
		coreEngine = new SudoCore(math::Vector2(800, 600), "SudoGameEngine", this);
	}

	void Update()
	{
		// Draw entity/s with renderer->Draw( );
		renderer->Draw(leftPaddle->GetComponent<ecs::RectangleComponent>("RectangleComponent"));
		renderer->Draw(rightPaddle->GetComponent<ecs::RectangleComponent>("RectangleComponent"));

		if (input->IsKeyPressed(GLFW_KEY_W))
			leftPaddle->transform->Move(math::Vector3(0, -4, 0));
		if (input->IsKeyPressed(GLFW_KEY_S))
			leftPaddle->transform->Move(math::Vector3(0, 4, 0));

		if (input->IsKeyPressed(GLFW_KEY_UP))
			rightPaddle->transform->Move(math::Vector3(0, -4, 0));
		if (input->IsKeyPressed(GLFW_KEY_DOWN))
			rightPaddle->transform->Move(math::Vector3(0, 4, 0));
	}
		
	void Start() 
	{
		settings->SetFPS(120);

		// Create shape entity, add rectangle component then change it's position
		leftPaddle = new ecs::Entity("left_paddle");
		leftPaddle->AddComponent(new ecs::RectangleComponent(math::Vector2(20,100), math::Vector4(1,0,0,1)));
		leftPaddle->transform->position = math::Vector3(30, 400, 0);

		rightPaddle = new ecs::Entity("right_paddle");
		rightPaddle->AddComponent(new ecs::RectangleComponent(math::Vector2(20, 100), math::Vector4(1, 0, 0, 1)));
		rightPaddle->transform->position = math::Vector3(800 - 20 - 30, 100, 0);
	}
};

int main() {
	App* app = new App();

	return EXIT_SUCCESS;
}