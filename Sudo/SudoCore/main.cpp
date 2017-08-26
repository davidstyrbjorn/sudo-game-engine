#include<iostream>
#include"core\sudo.h"

using namespace sudo;

#include"core\src\ecs\entity.h"
#include"core\src\ecs\component.h"
#include"core\src\ecs\test_component.h"

class NotDerivedComponent {

};

/* Sandbox for testing implemented features */
class App : SudoClass {

private:
	CoreEngine *coreEngine;
	system::WorldSystem *world = system::WorldSystem::Instance();
	system::InputSystem *input = system::InputSystem::Instance();

	uint VAO;
	uint VBO;
	uint EBO; // Inidices buffer
	graphics::Shader *shader;

	ecs::Entity *player;

	float x = (800/2)-(60/2);
	float y = (600/2)-(60/2);
	float width = 60;
	float height = 60;

public:
	App() 
	{
		coreEngine = new CoreEngine(math::Vector2(800, 600), "Pong", this);
	}

	void Update()
	{
		// Draw object
		shader->bind();
		shader->setUniformMatrix4x4("model_matrix", math::Matrix4x4::Translation(math::Vector3(x, y, 0.0)));

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
							
	void Start() 
	{
		glewInit();
		glewExperimental = true;

		player = new ecs::Entity("player");
		player->AddComponent(new ecs::TestComponent);
		// Goal
		if (player->GetComponent<ecs::TestComponent>("TestComponent") != nullptr) {

		}

		shader = new graphics::Shader("D:\\SudoGameEngine\\Sudo\\SudoCore\\core\\src\\shader_vertex.txt", "D:\\SudoGameEngine\\Sudo\\SudoCore\\core\\src\\shader_fragment.txt");
		shader->bind();
		shader->setUniformMatrix4x4("projection_matrix", math::Matrix4x4::Orthographic(0, 800, 600, 0,-1,1));
		shader->setUniform3f("color", math::Vector3(0, 1, 1));

		// Vertex points
		float vertices[] = {
			0,0,0.0f,			// bottom-left
			width, height,0.0f, // bottom-right
			0, height,0.0f,		// top-left
			width,0.0f,0.0f		// top-right
		};

		uint indices[] = {
			0,1,2,0, // Triangle N.1
			1,3,2  // Triangle N.2
		};

		// Create element buffer object
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		// Creating and binding the Vertex Array Object
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		// Creating the buffer object
		glGenBuffers(1, &VBO);

		// Copy our vertices array into a buffer for OpenGL to use
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Linking/setting our vertex attributes
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}
};

int main() {
	App *app = new App();

	return EXIT_SUCCESS;
}