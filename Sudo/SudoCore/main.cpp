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
	ecs::Entity *staticShape;
	ecs::BoxCollider2D *shapeBoxCollider;
	ecs::BoxCollider2D *staticBoxCollider;
public:
	App() 
	{
		coreEngine = new SudoCore(math::Vector2(800, 600), "SudoGameEngine", this);
	}

	void Update()
	{
		// Draw entity/s with renderer->Draw( );
		renderer->Draw(shape->GetComponent<ecs::RectangleComponent>("RectangleComponent"));
		renderer->Draw(staticShape->GetComponent<ecs::RectangleComponent>("RectangleComponent"));

		if (shapeBoxCollider->Intersects(*staticBoxCollider)) {
			
		}

		if (input->IsKeyPressed(GLFW_KEY_A)) {
			shape->transform->Move(math::Vector3(-5, 0, 0));
		}
		if (input->IsKeyPressed(GLFW_KEY_D)) {
			shape->transform->Move(math::Vector3(5, 0, 0));
		}
		if (input->IsKeyPressed(GLFW_KEY_S)) {
			shape->transform->Move(math::Vector3(0, 5, 0));
		}
		if (input->IsKeyPressed(GLFW_KEY_W)) {
			shape->transform->Move(math::Vector3(0, -5, 0));
		}
	}
		
	void Start() 
	{
		// Create shape entity, add rectangle component then change it's position
		shape = new ecs::Entity("shape");
		shape->AddComponent(new ecs::RectangleComponent(math::Vector2(50,50), math::Vector4(1,0,0,1)));
		shape->transform->position = math::Vector3((800/2)-(150/2), (600/2)-(150/2), 0);
		shape->AddComponent(new ecs::BoxCollider2D());
		shapeBoxCollider = shape->GetComponent<ecs::BoxCollider2D>("BoxCollider2D");

		staticShape = new ecs::Entity("shape2");
		staticShape->AddComponent(new ecs::RectangleComponent(math::Vector2(50, 50), math::Vector4(0, 1, 1, 1)));
		staticShape->transform->position = math::Vector3(50, (600 / 2) - (150 / 2), 0);
		staticShape->AddComponent(new ecs::BoxCollider2D());
		staticBoxCollider = shape->GetComponent<ecs::BoxCollider2D>("BoxCollider2D");
	}
};

int main() {
	App* app = new App();

	return EXIT_SUCCESS;
}