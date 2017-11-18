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

	int width = 14;
	int offset = 16;

	int quadSize = 100;
	int quadX = 200;
	int quadY = 200;

	int triangleSize = 200;
	int triangleX = 0;
	int triangleY = 0;

public:
	App() 
	{
		coreEngine.init(math::Vector2(800,600), "Sudo Game Engine", this);
	}

	void Update() override
	{
		// 3072 triangles with the batch renderer
		for (int x = 0; x < 24; x++) {
			for (int y = 0; y < 24; y++) {
				math::Vector4 colorVector = math::Vector4(sin(clock.GetTicks()*0.001f), cos(clock.GetTicks()*0.001f), 0.5f, 1);
				graphics::VertexData vertices[] = {
					graphics::VertexData(math::Vector3((offset*x),(offset*y),0),								colorVector, math::Vector2(0,0)), // Top left
					graphics::VertexData(math::Vector3((offset*x),(offset*y) + width,0),						colorVector, math::Vector2(0,0)), // Bottom left
					graphics::VertexData(math::Vector3((offset*x) + width,(offset*y) + width,0),				colorVector, math::Vector2(0,0)), // Bottom right
					graphics::VertexData(math::Vector3((offset*x) + width, (offset*y), 0),						colorVector, math::Vector2(0,0))  // Top right
				};
				m_batchRenderer->Submit(vertices, 4);
			}					
		}
		
		math::Vector4 colorVector = math::Vector4(1,0,0,1);
		graphics::VertexData triangle[] = {
			graphics::VertexData(math::Vector3(triangleX,triangleY,0),											colorVector, math::Vector2(0,0)), // Top left
			graphics::VertexData(math::Vector3(triangleX,triangleY + triangleSize,0),							colorVector, math::Vector2(0,0)), // Bottom left
			graphics::VertexData(math::Vector3(triangleX + triangleSize,triangleY + triangleSize,0),			colorVector, math::Vector2(0,0)) // Bottom right
		};

		colorVector = math::Vector4(0, 0, 1, 1);
		graphics::VertexData quad[] = {
			graphics::VertexData(math::Vector3(quadX,quadY,0),									colorVector, math::Vector2(0,0)), // Top left
			graphics::VertexData(math::Vector3(quadX,quadY + quadSize,0),						colorVector, math::Vector2(0,0)), // Bottom left
			graphics::VertexData(math::Vector3(quadX + quadSize,quadY + quadSize,0),			colorVector, math::Vector2(0,0)), // Bottom right
			graphics::VertexData(math::Vector3(quadX + quadSize, quadY, 0),						colorVector, math::Vector2(0,0))
		};
		//m_batchRenderer->Submit(triangle, 3); 
		//m_batchRenderer->Submit(quad, 4);
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