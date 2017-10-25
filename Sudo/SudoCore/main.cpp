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
		coreEngine.init(math::Vector2(800, 600), "Sudo Game Engine", this);
	}

	void Update() override
	{
		renderer->Draw(entity->GetComponent<ecs::RectangleComponent>());

		if (input->GetKey("d"))
			entity->transform->Move(math::Vector3(7, 0, 0));
		if (input->GetKey("a"))
			entity->transform->Move(math::Vector3(-7, 0, 0));
		if (input->GetKey("s"))
			entity->transform->Move(math::Vector3(0, 7, 0));
		if (input->GetKey("w"))
			entity->transform->Move(math::Vector3(0, -7, 0));
		
		if (input->GetKey("f")) {
			entity->GetComponent<ecs::SoundComponent>()->GetSoundSource()->play();
			entity->GetComponent<ecs::RectangleComponent>()->SizeUp(5);
		}
		if (input->GetKey("x")) {
			entity->GetComponent<ecs::SoundComponent>()->GetSoundSource()->stop();
		}
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