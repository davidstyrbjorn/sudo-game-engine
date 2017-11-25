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

	std::vector<ecs::RectangleComponent*> m_rectangleComponentEntities;

	int offset = 22;

public:
	App() 
	{
		coreEngine.init(math::Vector2(800,500), "Sudo Game Engine", this);
	}

	void Update() override
	{
		for (int i = 0; i < m_rectangleComponentEntities.size(); i++) {
			renderer->Submit(m_rectangleComponentEntities[i]);
		}
	}	

	void Start() override
	{
		// Genereate alot of rectangles
		for (int x = 0; x < 36; x++)
		{
			for (int y = 0; y < 23; y++) 
			{
				ecs::Entity *thing = new ecs::Entity("thing_thing");
				thing->AddComponent(new ecs::RectangleComponent(math::Vector2(20, 20), math::Color(1, 0.1f, 0.25f, 1)));
				thing->transform->position = math::Vector3(x*offset, y*offset, 0);

				m_rectangleComponentEntities.push_back(thing->GetComponent<ecs::RectangleComponent>());
			}
		}

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