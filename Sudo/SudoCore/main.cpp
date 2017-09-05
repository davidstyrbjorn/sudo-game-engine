#include<iostream>
#include"core\sudo.h"

using namespace sudo;

/* Sandbox for testing implemented features */
class App : SudoClass {

private:
	SudoCore *coreEngine;
	system::InputSystem *input = system::InputSystem::Instance();
	system::RenderSystem *renderer = system::RenderSystem::Instance();

	//uint EBO; // Inidices buffer
	graphics::Shader *shader;

	ecs::Entity *shape;
	ecs::Entity *shape2;

public:
	App() 
	{
		coreEngine = new SudoCore(math::Vector2(800, 600), "SudoGameEngine", this);
	}

	void Update()
	{
		// Draw entity with RectangleComponent
		renderer->Draw(shape->GetComponent<ecs::RectangleComponent>("RectangleComponent"));
		renderer->Draw(shape2->GetComponent<ecs::TriangleComponent>("TriangleComponent"));
	}
		
	void Start() 
	{
		// Create shape entity, add rectangle component then change it's position
		shape = new ecs::Entity("shape");
		shape->AddComponent(new ecs::RectangleComponent(math::Vector2(70,120)));
		shape->transform->position = math::Vector3(300, 100, 0);

		shape2 = new ecs::Entity("shape2");
		shape2->AddComponent(new ecs::TriangleComponent(math::Vector2(600, 300)));
		shape2->transform->position = math::Vector3(50, 50, 0);
	}
};

int main() {
	App* app = new App();

	return EXIT_SUCCESS;
}