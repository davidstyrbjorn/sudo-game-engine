#include<iostream>
#include"core\sudo.h"

using namespace sudo;
using namespace utility;

/* Sandbox for testing implemented features */
class App : SudoClass {

private:
	SudoCore coreEngine;

	sudo_system::BatchRendererSystem *m_batchRenderer = sudo_system::BatchRendererSystem::Instance();

	ecs::Entity *shape, *shape2, *shape3;

public:
	App() 
	{
		coreEngine.init(math::Vector2(800,600), "Sudo Game Engine", this);
	}

	void Update() override
	{
#if 0
		// 3072 triangles with the batch renderer
		for (int x = 0; x < 14; x++) {
			for (int y = 0; y < 14; y++) {
				math::Vector4 colorVector = math::Vector4(1, 0.4f, 0.5f, 1);
				graphics::VertexData vertices[] = {
					graphics::VertexData(math::Vector3((offset*x),(offset*y),0),								colorVector, math::Vector2(0,0)), // Top left
					graphics::VertexData(math::Vector3((offset*x),(offset*y) + width,0),						colorVector, math::Vector2(0,0)), // Bottom left
					graphics::VertexData(math::Vector3((offset*x) + width,(offset*y) + width,0),				colorVector, math::Vector2(0,0)) // Bottom right
					//graphics::VertexData(math::Vector3((offset*x) + width, (offset*y), 0),						colorVector, math::Vector2(0,0))  // Top right
				};
				m_batchRenderer->Submit(vertices, 4);
			}					
		}
		for (int x = 14; x < 28; x++) {
			for (int y = 14; y < 28; y++) {
				math::Vector4 colorVector = math::Vector4(0.4f, 1, 0.5f, 1);
				graphics::VertexData vertices[] = {
					graphics::VertexData(math::Vector3((offset*x),(offset*y),0),								colorVector, math::Vector2(0,0)), // Top left
					graphics::VertexData(math::Vector3((offset*x),(offset*y) + width,0),						colorVector, math::Vector2(0,0)), // Bottom left
					graphics::VertexData(math::Vector3((offset*x) + width,(offset*y) + width,0),				colorVector, math::Vector2(0,0)), // Bottom right
					graphics::VertexData(math::Vector3((offset*x) + width, (offset*y), 0),						colorVector, math::Vector2(0,0))  // Top right
				};
				m_batchRenderer->Submit(vertices, 4);
			}
		}
#endif
		//m_batchRenderer->Submit(shape->GetComponent<ecs::TriangleComponent>(), 3);
		m_batchRenderer->Submit(shape2->GetComponent<ecs::RectangleComponent>(), 6);

		if (input->GetKey("d"))
			shape2->transform->Move(math::Vector3::Right() * +8);
		if (input->GetKey("a"))
			shape2->transform->Move(math::Vector3::Right() * -8);
		if (input->GetKey("s"))
			shape2->transform->Move(math::Vector3::Down() * +8);
		if (input->GetKey("w"))
			shape2->transform->Move(math::Vector3::Up() * +8);
	}

	void Start() override
	{
		config->SetFPS(60);
		config->SetBackgroundColor(math::Vector4(0.05f, 0.0f, 0.05f, 1));

		shape = new ecs::Entity("shape");
		shape->AddComponent(new ecs::TriangleComponent(math::Vector2(100, 100), math::Vector4(0, 0.5f, 1, 1)));

		shape2 = new ecs::Entity("shape");
		shape2->AddComponent(new ecs::RectangleComponent(math::Vector2(150, 150), math::Vector4(1, 0, 0.25f, 1)));
	}
};

int main() 
{
	App* app = new App();

	return EXIT_SUCCESS;
}