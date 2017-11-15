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

	int triangleWidth = 10;
	int offset = 11;

public:
	App() 
	{
		coreEngine.init(math::Vector2(800, 600), "Sudo Game Engine", this);
	}

	void Update() override
	{
		for (int x = 0; x < 64; x++) {
			for (int y = 0; y < 48; y++) {
				math::Vector4 colorVector = math::Vector4(1, 0, 0, 1);
				graphics::VertexData vertices[] = {
					graphics::VertexData(math::Vector3((offset*x),(offset*y),0),										colorVector, math::Vector2(0,0)), // Top left
					graphics::VertexData(math::Vector3((offset*x),(offset*y) + triangleWidth,0),						colorVector, math::Vector2(0,0)), // Bottom left
					graphics::VertexData(math::Vector3((offset*x) + triangleWidth,(offset*y) + triangleWidth,0),		colorVector, math::Vector2(0,0))  // Bottom right
				};
				m_batchRenderer->Submit(vertices);
			}
		}
	}

	void Start() override
	{		   

		config->SetFPS(60);
		config->SetBackgroundColor(math::Vector4(0.1, 0.1, 0.1, 1));
	}
};

int main() 
{
	App* app = new App();

	return EXIT_SUCCESS;
}