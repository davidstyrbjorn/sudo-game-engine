#include<iostream>
#include"core\sudo.h"

using namespace sudo;

/* Sandbox for testing implemented features */
class App : SudoClass {

private:
	SudoCore *coreEngine;
	system::InputSystem *input = system::InputSystem::Instance();
	system::RenderSystem *renderer = system::RenderSystem::Instance();

	ecs::Entity *shape;
	ecs::Entity *shape2;
	ecs::Entity *shape3;

public:
	App() 
	{
		coreEngine = new SudoCore(math::Vector2(800, 600), "SudoGameEngine", this);
	}

	void Update()
	{
		// Draw entity with Entities
		renderer->Draw(shape->GetComponent<ecs::RectangleComponent>("RectangleComponent"));
		renderer->Draw(shape2->GetComponent<ecs::TriangleComponent>("TriangleComponent"));
		renderer->Draw(shape3->GetComponent<ecs::TriangleComponent>("TriangleComponent"));
	}
		
	void Start() 
	{
		// Create shape entity, add rectangle component then change it's position
		shape = new ecs::Entity("shape");
		shape->AddComponent(new ecs::RectangleComponent(math::Vector2(150,150), math::Vector4(1,0,0,1)));
		shape->transform->position = math::Vector3((800/2)-(150/2), (600/2)-(150/2), 0);

		shape2 = new ecs::Entity("shape2");
		shape2->AddComponent(new ecs::TriangleComponent(math::Vector2(100, 100), math::Vector4(0,1,0,1)));
		shape2->transform->position = math::Vector3(50, 50, 0);

		shape3 = new ecs::Entity("shape2");
		shape3->AddComponent(new ecs::TriangleComponent(math::Vector2(100, 100), math::Vector4(0,0,1,1)));
		shape3->transform->position = math::Vector3(650, 450, 0);

		// Change background color
		coreEngine->dab();
	}
};

int main() {
	App* app = new App();

	return EXIT_SUCCESS;
}