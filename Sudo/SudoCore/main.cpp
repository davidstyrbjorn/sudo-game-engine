#include<iostream>
#include"core\sudo.h"

using namespace sudo;
using namespace utility;

/* Sandbox for testing implemented features */
class App : SudoClass {

private:
	SudoCore coreEngine;

	ecs::Entity *entity, *entity2;
	
public:
	App() 
	{
		coreEngine.init(math::Vector2(800, 600), "Sudo Game Engine", this);
	}

	void Update()
	{
		renderer->Draw(entity2->GetComponent<ecs::SpriteComponent>());
		renderer->Draw(entity->GetComponent<ecs::SpriteComponent>());
	}

	void Start() override
	{
		entity = new ecs::Entity("image");
		entity->AddComponent(new ecs::SpriteComponent("D:\\temp\\sqyare.png"));
		entity->GetComponent<ecs::SpriteComponent>()->SetColor(math::Vector4(1, 1, 1, 0.5f));

		entity2 = new ecs::Entity("image2");
		entity2->AddComponent(new ecs::SpriteComponent("D:\\temp\\square.png"));

		config->SetFPS(120);
		config->SetBackgroundColor(math::Vector4(0.1, 0.1, 0.1, 1));
	}
};

int main() 
{
	App* app = new App();

	return EXIT_SUCCESS;
}
