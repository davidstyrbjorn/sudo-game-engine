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
		renderer->Draw(entity->GetComponent<ecs::RectangleComponent>());

		if (input->GetKey("f"))
			entity->GetComponent<ecs::SoundComponent>()->GetSoundSource()->play();
	}

	void Start() override
	{	
		entity = new ecs::Entity("image");     
		entity->AddComponent(new ecs::RectangleComponent(math::Vector2(40, 40), math::Vector4(1, 1, 0, 1)));
		entity->AddComponent(new ecs::SoundComponent("D:\\temp\\sound.wav"));

		config->SetFPS(60);
		config->SetBackgroundColor(math::Vector4(0.1, 0.1, 0.1, 1));
	}
};

int main() 
{
	App* app = new App();

	return EXIT_SUCCESS;
}
