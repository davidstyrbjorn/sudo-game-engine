#include<iostream>
#include"core\sudo.h"

using namespace sudo;
using namespace utility;

// Sandbox for testing implemented features 
class App : SudoClass {

private:
	SudoCore coreEngine;

	ecs::Entity *shape, *shape2;
	graphics::Texture *texture1, *texture2;

public:
	App() 
	{
		coreEngine.init(math::Vector2(800,500), "Sudo Game Engine", this);
	}

	void Update(float deltaTime) override
	{
		textRenderer->DrawText("Viktor.net", math::Vector2(0, 0), math::Color(200, 20, 160));
		renderer->Submit(shape->GetComponent<ecs::RectangleComponent>());
	
		if (input->GetKey("space")) {
			sudo_system::ParticleConfiguration config = sudo_system::ParticleConfiguration();
			config.DoFade = true;
			config.GravitySimulated = true;
			config.GravityScale = -0.001f * sin(deltaTime);

			particleSystem->Submit(shape->transform->position,
				math::Vector2(3, 3),
				math::Color(utility::SudoRandomNumber::GetRandomInteger(0,255), utility::SudoRandomNumber::GetRandomInteger(0, 255), utility::SudoRandomNumber::GetRandomInteger(0, 255), 255),
				1000,
				math::Vector2(utility::SudoRandomNumber::GetRandomFloatingPoint(-0.5f, 0.5f), utility::SudoRandomNumber::GetRandomFloatingPoint(-0.5f, 0.5f)),
				config
			);
		}

		if (input->GetKey("d"))
			shape->transform->Move(math::Vector3::Right() * 0.25f * deltaTime);
		if (input->GetKey("a"))
			shape->transform->Move(math::Vector3::Left() * 0.25f * deltaTime);
		if (input->GetKey("s"))
			shape->transform->Move(math::Vector3::Down() * 0.25f * deltaTime);
		if (input->GetKey("w"))
			shape->transform->Move(math::Vector3::Up() * 0.25f * deltaTime);
	}	

	void Start() override
	{
		shape = new ecs::Entity("shape");
		shape->AddComponent(new ecs::RectangleComponent(math::Vector2(10, 10), math::Color(255, 100, 10, 255)));
		shape->transform->position = math::Vector3(400, 300, 0);

		//config->SetFPS(60);
		config->SetBackgroundColor(math::Vector4(0.05f, 0.0f, 0.05f, 1));
	}

	void OnApplicationQuit() override 
	{
		delete texture1;
		delete texture2;
	}
};

int madawin() {
	App* app = new App();

	return 0;
}