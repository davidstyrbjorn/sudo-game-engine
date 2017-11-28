#include<iostream>
#include"core\sudo.h"

using namespace sudo;
using namespace utility;

/* Sandbox for testing implemented features */
class App : SudoClass {

private:
	SudoCore coreEngine;

	sudo_system::BatchRendererSystem *m_batchRenderer = sudo_system::BatchRendererSystem::Instance();

	ecs::Entity *shape;

	graphics::Texture *texture1, *texture2;

	std::vector<ecs::RectangleComponent*> m_rectangleComponentEntities;

	int offset = 22;

public:
	App() 
	{
		coreEngine.init(math::Vector2(800,500), "Sudo Game Engine", this);
	}

	void Update(float deltaTime) override
	{
		for (int i = 0; i < m_rectangleComponentEntities.size(); i++) {
			renderer->Submit(m_rectangleComponentEntities[i]);
		}
		renderer->Submit(shape->GetComponent<ecs::RectangleComponent>());
		
		/*
		if (input->GetKey("d"))
			shape->transform->Move(math::Vector3::Right() * 0.4f * deltaTime);
		if (input->GetKey("a"))
			shape->transform->Move(math::Vector3::Left() * 0.4f * deltaTime);
		if (input->GetKey("s"))
			shape->transform->Move(math::Vector3::Down() * 0.4f * deltaTime);
		if (input->GetKey("w"))
			shape->transform->Move(math::Vector3::Up() * 0.4f * deltaTime);
			*/
	}	

	void FixedUpdate() 
	{
		if (input->GetKey("d"))
			shape->transform->Move(math::Vector3::Right() * 0.4f);
		if (input->GetKey("a"))
			shape->transform->Move(math::Vector3::Left() * 0.4f);
		if (input->GetKey("s"))
			shape->transform->Move(math::Vector3::Down() * 0.4f);
		if (input->GetKey("w"))
			shape->transform->Move(math::Vector3::Up() * 0.4f);
	}

	void Start() override
	{
		// Genereate alot of rectangles
		for (int x = 0; x < 36; x++)
		{
			for (int y = 0; y < 23; y++) 
			{
				ecs::Entity *thing = new ecs::Entity("thing_thing");
				thing->AddComponent(new ecs::RectangleComponent(math::Vector2(20, 20), math::Color(255,0,0,255)));
				thing->transform->position = math::Vector3(x*offset, y*offset, 0);

				m_rectangleComponentEntities.push_back(thing->GetComponent<ecs::RectangleComponent>());
			}
		}

		shape = new ecs::Entity("shape");
		shape->AddComponent(new ecs::RectangleComponent(math::Vector2(50, 50), math::Color(255, 0, 255, 255)));

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