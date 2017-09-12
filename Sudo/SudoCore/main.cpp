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

	ecs::Entity *shape;
	
public:
	App() 
	{
		coreEngine = new SudoCore(math::Vector2(800, 600), "SudoGameEngine", this);
	}

	void Update()
	{
		// Draw entity/s with renderer->Draw( );
		renderer->Draw(shape->GetComponent<ecs::RectangleComponent>("RectangleComponent"));
	}
		
	void Start() 
	{
		settings->SetFPS(60);

		// Create shape entity, add rectangle component then change it's position
		shape = new ecs::Entity("shape");
		shape->AddComponent(new ecs::RectangleComponent(math::Vector2(50,50), math::Vector4(1,0,0,1)));
		shape->transform->position = math::Vector3((800/2)-(150/2), (600/2)-(150/2), 0);
	}
};

int main() {
	App* app = new App();

	return EXIT_SUCCESS;
}