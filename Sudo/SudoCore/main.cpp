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
		// Draw object
		renderer->Draw(shape->GetComponent<ecs::RectangleComponent>("RectangleComponent"));
		renderer->Draw(shape2->GetComponent<ecs::RectangleComponent>("RectangleComponent"));
	}
							
	void Start() 
	{
		shape = new ecs::Entity("shape");
		shape->AddComponent(new ecs::RectangleComponent());
		shape->transform->position = math::Vector3(100, 100, 0);

		shape2 = new ecs::Entity("shape2");
		shape2->AddComponent(new ecs::RectangleComponent());
	}
};

int main() {
	App* app = new App();

	return EXIT_SUCCESS;
}