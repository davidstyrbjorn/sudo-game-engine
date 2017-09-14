#include<iostream>
#include"core\sudo.h"

#include<array>

using namespace sudo;

/* Sandbox for testing implemented features */
class App : SudoClass {

private:
	SudoCore *coreEngine;

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

		// Examples
		if (input->GetKey("s")) {
			leftPaddle->transform->Move(math::Vector3(0, 4, 0));
		}
		if (input->GetKey("w")) {
			leftPaddle->transform->Move(math::Vector3(0, -4, 0));
		}
	}

	void Start() 
	{
		// Create shape entity, add rectangle component then change it's position
		leftPaddle = new ecs::Entity("left_paddle");
		leftPaddle->AddComponent(new ecs::RectangleComponent(math::Vector2(20,100), math::Vector4(1,0,0,1)));
		leftPaddle->transform->position = math::Vector3(30, 400, 0);
		leftPaddle->GetComponent<ecs::RectangleComponent>("RectangleComponent")->SetComponentState(ecs::ComponentState::DISABLED);

		rightPaddle = new ecs::Entity("right_paddle");
		rightPaddle->AddComponent(new ecs::RectangleComponent(math::Vector2(20, 100), math::Vector4(1, 0, 0, 1)));
		rightPaddle->transform->position = math::Vector3(800 - 20 - 30, 100, 0);

		config->SetFPS(120);
		config->SetBackgroundColor(math::Vector4(0.1, 0.1, 0.1, 1));
	}
};

int main() {
	App* app = new App();

	return EXIT_SUCCESS;
}