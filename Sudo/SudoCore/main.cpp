#include<iostream>
#include"core\sudo.h"

using namespace sudo;
using namespace utility;

/* Sandbox for testing implemented features */
class App : SudoClass {

private:
	SudoCore coreEngine;

	ecs::Entity *entity;
	
public:
	App() 
	{
		coreEngine.init(math::Vector2(600, 400), "Sudo Game Engine", this);
	}

	void Update() override
	{
		renderer->Draw(entity->GetComponent<ecs::SpriteComponent>());
		if (input->GetKey("x"))
			entity->transform->angle += 0.5f;
	}

	void Start() override
	{
		entity = new ecs::Entity("image");     
		entity->AddComponent(new ecs::SpriteComponent("C:\\temp\\cat.png"));
		//entity->GetComponent<ecs::SpriteComponent>()->SetColor(math::Vector4(1, 1, 1, 0.5f));

		config->SetFPS(60);
		config->SetBackgroundColor(math::Vector4(0.1, 0.1, 0.1, 1));
	}
};

int main() 
{
	App* app = new App();

	return EXIT_SUCCESS;
}
