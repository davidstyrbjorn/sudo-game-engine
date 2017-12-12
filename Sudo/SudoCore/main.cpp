#include<iostream>
#include"core\sudo.h"

using namespace sudo;
using namespace utility;

// Sandbox for testing implemented features 
class App : SudoClass {

private:
	SudoCore coreEngine;

	ecs::Entity *shape, *shape2;

public:
	App() 
	{
		coreEngine.init(math::Vector2(800,500), "Sudo Game Engine", this);
	}

	void Update(float deltaTime) override
	{
		textRenderer->DrawText("Viktor.net", math::Vector2(shape->transform->position.x, 0), math::Color(57, 171, 233));
		renderer->Submit(shape->GetComponent<ecs::RectangleComponent>());
		renderer->Submit(shape2->GetComponent<ecs::SpriteComponent>());
	
		if (input->GetKey("space")) {
			sudo_system::ParticleConfiguration config = sudo_system::ParticleConfiguration();
			config.DoFade = true;
			config.GravitySimulated = true;
			config.GravityScale = 0.001f;

			particleSystem->Submit(shape->transform->position,
				math::Vector2(3, 3),
				math::Color(utility::SudoRandomNumber::GetRandomInteger(0,255), utility::SudoRandomNumber::GetRandomInteger(0, 255), utility::SudoRandomNumber::GetRandomInteger(0, 255), 255),
				1000,
				math::Vector2(utility::SudoRandomNumber::GetRandomFloatingPoint(-0.5f, 0.5f)+0.1f, utility::SudoRandomNumber::GetRandomFloatingPoint(-0.5f, 0.5f)+0.1f),
				config
			);
		}

		// Font test
		if (input->GetKey("f")) 
		{
			textRenderer->SetFont("CAPITAL HILL FONT PLEASE", 50);
		}
		if (input->GetKey("d"))
		{
			textRenderer->SetFont("default", 20);
		}
	}	

	void FixedUpdate() override
	{
		shape2->transform->angle += 0.01f;
	}

	void Start() override
	{
		shape = new ecs::Entity();
		shape->AddComponent(new ecs::RectangleComponent(math::Vector2(10, 10), math::Color(255, 100, 10, 255)));
		shape->transform->position = math::Vector3(400, 300, 0);
		shape->AddComponent(new ecs::FourWayMoveComponent(math::Vector2(0.3f, 0.3f), "up", "down", "right", "left"));

		shape2 = new ecs::Entity();
		shape2->AddComponent(new ecs::SpriteComponent("D:\\temp\\cat.png"));

		textRenderer->LoadFont("C:\\Windows\\Fonts\\comic.ttf", "CAPITAL HILL FONT PLEASE", 50);

		//config->SetFPS(60);
		config->SetBackgroundColor(math::Color(0.05f*255, 0.0f, 0.05f*255, 1));
	} 
};

int maidwdwn() {
	App* app = new App();

	return 0;
}