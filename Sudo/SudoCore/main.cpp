#include<iostream>
#include"core\sudo.h"

#include<array>

using namespace sudo;

/* Sandbox for testing implemented features */
class App : SudoClass {

private:
	SudoCore *coreEngine;

	ecs::Entity *leftPaddle, *rightPaddle, *triangle;
	
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
		renderer->Draw(triangle->GetComponent<ecs::TriangleComponent>("TriangleComponent"));
	}

	void Start() 
	{
		// Create shape entity, add rectangle component then change it's position
		leftPaddle = new ecs::Entity("left_paddle");
		leftPaddle->AddComponent(new ecs::RectangleComponent(math::Vector2(220,220), math::Vector4(1,0,0,1)));
		leftPaddle->transform->Move(math::Vector3(25, 25, 0));

		rightPaddle = new ecs::Entity("right_paddle");
		rightPaddle->AddComponent(new ecs::RectangleComponent(math::Vector2(100, 100), math::Vector4(0, 1, 1, 1)));
		rightPaddle->transform->Move(math::Vector3(150, 150, 0));

		triangle = new ecs::Entity("triangle");
		triangle->AddComponent(new ecs::TriangleComponent(math::Vector2(150, 150), math::Vector4(1, 1, 0, 1)));
		triangle->transform->Move(math::Vector3(370, 320, 0));

		config->SetFPS(120);
		config->SetBackgroundColor(math::Vector4(0.1, 0.1, 0.1, 1));
	}
};

int main() 
{
	App* app = new App();

	return EXIT_SUCCESS;
}