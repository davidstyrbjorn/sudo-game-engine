#include<iostream>
#include"core\sudo.h"

using namespace sudo;
using namespace utility;

/* Sandbox for testing implemented features */
class App : SudoClass {

private:
	SudoCore coreEngine;

	sudo_system::BatchRendererSystem *m_batchRenderer = sudo_system::BatchRendererSystem::Instance();

	ecs::Entity *shape, *shape2, *sprite1;

	graphics::Texture *texture1, *texture2;

public:
	App() 
	{
		coreEngine.init(math::Vector2(800,500), "Sudo Game Engine", this);
	}

	void Update() override
	{
		renderer->Submit(shape->GetComponent<ecs::RectangleComponent>());
		renderer->Submit(shape2->GetComponent<ecs::RectangleComponent>());
		renderer->Submit(sprite1->GetComponent<ecs::SpriteComponent>());
	}	

	void Start() override
	{
		shape = new ecs::Entity("shape");
		shape->AddComponent(new ecs::RectangleComponent(math::Vector2(100, 100), math::Vector4(0.25f, 0.1f, 0.8f, 1)));

		shape2 = new ecs::Entity("shape");
		shape2->AddComponent(new ecs::RectangleComponent(math::Vector2(200, 200), math::Vector4(1.0f, 0.1f, 0.8f, 1)));
		shape2->transform->Move(math::Vector3(120, 120, 0));

		sprite1 = new ecs::Entity("sprite");
		sprite1->AddComponent(new ecs::SpriteComponent("D:\\temp\\cat.png"));
		sprite1->transform->Move(math::Vector3(300, 300, 0));

		//config->SetFPS(60);
		config->SetBackgroundColor(math::Vector4(0.05f, 0.0f, 0.05f, 1));
	}

	void OnApplicationQuit() override 
	{
		delete texture1;
		delete texture2;
	}
};

int main() 
{
	App* app = new App();

	return EXIT_SUCCESS;
}