#include<iostream>
#include"core\sudo.h"

using namespace sudo;

/* Sandbox for testing implemented features */
class App : SudoClass {

private:
	SudoCore *coreEngine;

	ecs::Entity *sprite, *sprite2;
	
public:
	App() 
	{
		coreEngine = new SudoCore(math::Vector2(800,600), "SudoGameEngine", this);
	}

	void Update()
	{
		// Draw entity/s with renderer->Draw( );
		renderer->Draw(sprite2->GetComponent<ecs::SpriteComponent>("SpriteComponent"));
		renderer->Draw(sprite->GetComponent<ecs::RectangleComponent>("RectangleComponent"));

		if (input->GetKey("d"))
			sprite->transform->Move(math::Vector3::Right() * 3);
		if (input->GetKey("a"))
			sprite->transform->Move(math::Vector3::Left() * 3);
		if (input->GetKey("s"))
			sprite->GetComponent<ecs::RectangleComponent>("RectangleComponent")->SetColor(math::Vector4(0, 1, 1, 1));
		if (input->GetKey("w"))
			sprite->GetComponent<ecs::RectangleComponent>("RectangleComponent")->SetColor(math::Vector4(1, 1, 0, 1));
		if (input->GetKey("c"))
			sprite2->transform->Move(math::Vector3::Right() * 2);
	}

	void Start() 
	{
		// Create shape entity, add rectangle component then change it's position
		sprite = new ecs::Entity("sprite");
		sprite->AddComponent(new ecs::RectangleComponent(math::Vector2(200, 200), math::Vector4(1, 0, 0, 1)));
		sprite->transform->Move(math::Vector3(350, 350, 0));

		//std::cout << (typeid(*sprite->GetComponent<ecs::RectangleComponent>("RectangleComponent")).name()) << std::endl;
		//std::cout << strlen(typeid(*sprite->GetComponent<ecs::RectangleComponent>("RectangleComponent")).name()) << std::endl;

		sprite2 = new ecs::Entity("sprite2");
		sprite2->AddComponent(new ecs::SpriteComponent("D:\\temp\\cat.png"));

		config->SetFPS(120);
		config->SetBackgroundColor(math::Vector4(0.1, 0.1, 0.1, 1));
	}
};

int main() 
{
	App* app = new App();

	return EXIT_SUCCESS;
}