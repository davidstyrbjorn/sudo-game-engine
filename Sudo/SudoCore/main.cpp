#include<iostream>
#include"core\sudo.h"

#include<array>

using namespace sudo;

/* Sandbox for testing implemented features */
class App : SudoClass {

private:
	SudoCore *coreEngine;

	ecs::Entity *sprite;
	
public:
	App() 
	{
		coreEngine = new SudoCore(math::Vector2(800, 600), "SudoGameEngine", this);
	}

	void Update()
	{
		// Draw entity/s with renderer->Draw( );
		renderer->Draw(sprite->GetComponent<ecs::SpriteComponent>("SpriteComponent"));
	}

	void Start() 
	{
		// Create shape entity, add rectangle component then change it's position
		sprite = new ecs::Entity("sprite");
		sprite->AddComponent(new ecs::SpriteComponent("C:\\temp\\sample.jpg", math::Vector2(300, 200)));

		config->SetFPS(120);
		config->SetBackgroundColor(math::Vector4(0.1, 0.1, 0.1, 1));
	}
};

int main() 
{
	App* app = new App();

	return EXIT_SUCCESS;
}