#include<iostream>
#include"core\sudo.h"

#include<vector>

using namespace sudo;

void test(double a ...) {
	std::vector<double> list;
	list.push_back(a);

	for (int i = 0; i < list.size(); i++) {
		std::cout << list.at(i) << ", " << std::endl;
	}
}

/* Sandbox for testing implemented features */
class App : SudoClass {

private:
	SudoCore *coreEngine;

	ecs::Entity *sprite, *sprite2;
	
public:
	App() 
	{
		coreEngine = new SudoCore(math::Vector2(800, 600), "SudoGameEngine", this);
	}

	void Update()
	{
		// Draw entity/s with renderer->Draw( );
		renderer->Draw(sprite->GetComponent<ecs::SpriteComponent>("SpriteComponent"));
		renderer->Draw(sprite2->GetComponent<ecs::SpriteComponent>("SpriteComponent"));

		if (input->GetKey("d"))
			sprite->transform->Move(math::Vector3::Right()*3);
		if (input->GetKey("a"))
			sprite->transform->Move(math::Vector3::Left() * 3);
		if (input->GetKey("s"))
			sprite->transform->Move(math::Vector3::Down() * 3);
		if (input->GetKey("w"))
			sprite->transform->Move(math::Vector3::Up() * 3);
	}

	void Start() 
	{
		// Create shape entity, add rectangle component then change it's position
		sprite = new ecs::Entity("sprite");
		sprite->AddComponent(new ecs::SpriteComponent("D:\\temp\\sample.jpg"));
		sprite->transform->Move(math::Vector3(350, 350, 0));

		sprite2 = new ecs::Entity("sprite2");
		sprite2->AddComponent(new ecs::SpriteComponent("D:\\temp\\sample_texture.jpg"));

		config->SetFPS(120);
		config->SetBackgroundColor(math::Vector4(0.1, 0.1, 0.1, 1));

		test(-4, 1, 99, 12, 5);
	}
};

int main() 
{
	App* app = new App();

	return EXIT_SUCCESS;
}