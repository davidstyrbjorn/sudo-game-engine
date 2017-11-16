#include<iostream>
#include"core\sudo.h"

using namespace sudo;
using namespace utility;

math::Vector4 colorVector = math::Vector4(1, 0, 0, 1);
graphics::VertexData vertices[] = {
	graphics::VertexData(math::Vector3(0,0,0),			colorVector, math::Vector2(0,0)),
	graphics::VertexData(math::Vector3(0,120,0),			colorVector, math::Vector2(0,0)),
	graphics::VertexData(math::Vector3(120,120,0),		colorVector, math::Vector2(0,0))
};

/* Sandbox for testing implemented features */
class App : SudoClass {

private:
	SudoCore coreEngine;

	sudo_system::BatchRendererSystem *m_batchRenderer = sudo_system::BatchRendererSystem::Instance();
	utility::Timer clock;

	int width = 11;
	int offset = 14;

public:
	App() 
	{
		coreEngine.init(math::Vector2(1200, 700), "Sudo Game Engine", this);
	}

	void Update() override
	{
		// 3072 triangles with the batch renderer
		for (int x = 0; x < 86; x++) {
			for (int y = 0; y < 52; y++) {
				math::Vector4 colorVector = math::Vector4(sin(clock.GetTicks()*0.001f), cos(clock.GetTicks()*0.001f), 0.5f, 1);
				graphics::VertexData vertices[] = {
					graphics::VertexData(math::Vector3((offset*x),(offset*y),0),								colorVector, math::Vector2(0,0)), // Top left
					graphics::VertexData(math::Vector3((offset*x),(offset*y) + width,0),						colorVector, math::Vector2(0,0)), // Bottom left
					graphics::VertexData(math::Vector3((offset*x) + width,(offset*y) + width,0),				colorVector, math::Vector2(0,0)), // Bottom right
					graphics::VertexData(math::Vector3((offset*x) + width, (offset*y), 0),						colorVector, math::Vector2(0,0))
				};
				m_batchRenderer->Submit(vertices, 4);
			}
		}
	}

	void Start() override
	{		   
		config->SetFPS(60);
		config->SetBackgroundColor(math::Vector4(0.1, 0.1, 0.1, 1));

		clock.Start();
	}
};

int main() 
{
	App* app = new App();

	return EXIT_SUCCESS;
}