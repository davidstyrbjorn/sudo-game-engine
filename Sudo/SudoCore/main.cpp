/*
#include<iostream>
#include"core\sudo.h"

using namespace sudo;
using namespace utility;

// Sandbox for testing implemented features 
class App : SudoClass {

private:
	SudoCore coreEngine;

	ecs::Entity *shape, *shape2;

	graphics::Texture *texture1, *texture2;

	std::vector<ecs::RectangleComponent*> m_rectangleComponentEntities;

	sudo::sudo_system::ParticleSystem *particleSystem = sudo_system::ParticleSystem::Instance();

	int offset = 22;

public:
	App() 
	{
		coreEngine.init(math::Vector2(800,500), "Sudo Game Engine", this);
	}

	void Update(float deltaTime) override
	{
		renderer->Submit(shape->GetComponent<ecs::RectangleComponent>());

		if (input->GetKey("space")) {
			sudo_system::ParticleConfiguration config = sudo_system::ParticleConfiguration();
			config.DoFade = true;
			config.GravitySimulated = true;
			config.GravityScale = -0.001f * sin(deltaTime);

			particleSystem->Submit(shape->transform->position,
				math::Vector2(3, 3),
				math::Color(utility::SudoRandomNumber::GetRandomInteger(0,255), utility::SudoRandomNumber::GetRandomInteger(0, 255), utility::SudoRandomNumber::GetRandomInteger(0, 255), 255),
				1000,
				math::Vector2(utility::SudoRandomNumber::GetRandomFloatingPoint(-0.5f, 0.5f), utility::SudoRandomNumber::GetRandomFloatingPoint(-0.5f, 0.5f)),
				config
			);
		}

		if (input->GetKey("d"))
			shape->transform->Move(math::Vector3::Right() * 0.25f * deltaTime);
		if (input->GetKey("a"))
			shape->transform->Move(math::Vector3::Left() * 0.25f * deltaTime);
		if (input->GetKey("s"))
			shape->transform->Move(math::Vector3::Down() * 0.25f * deltaTime);
		if (input->GetKey("w"))
			shape->transform->Move(math::Vector3::Up() * 0.25f * deltaTime);
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
		shape->AddComponent(new ecs::RectangleComponent(math::Vector2(10, 10), math::Color(255, 100, 10, 255)));
		shape->transform->position = math::Vector3(400, 300, 0);

		//config->SetFPS(60);
		config->SetBackgroundColor(math::Vector4(0.05f, 0.0f, 0.05f, 1));
	}

	void OnApplicationQuit() override 
	{
		delete texture1;
		delete texture2;
	}
};
*/

#include"core\gl_include.h"
#include<map>

#include<iostream>

#include<ft2build.h>
#include FT_FREETYPE_H

#include"core/src/math/vector2.h"
#include"core/src/math/vector3.h"
#include"core/src/math/mat4.h"
#include"core/src/graphics/shader.h"

using namespace sudo;

int main()
{
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		std::cout << "ERROR_FREETYPE: Could not init FreeType Library" << std::endl;
	}

	system("pause>null");
	return 0;
}

/*
struct Character {
	unsigned int		TextureID;  // ID handle of the glyph texture
	sudo::math::Vector2 Size;       // Size of glyph
	sudo::math::Vector2 Bearing;    // Offset from baseline to left/top of glyph
	unsigned int		Advance;    // Offset to advance to next glyph
};

std::map<GLchar, Character> Characters;
GLuint VAO, VBO;

void RenderText(graphics::Shader &shader, std::string text, float x, float y, float scale, math::Vector3 color) {
	shader.enable();
	shader.setUniform3f("textColor", color);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];

		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

int main() 
{
	//App* app = new App();

	// GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "Text", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glViewport(0, 0, 800, 600);

	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		std::cout << "ERROR_FREETYPE: Could not init FreeType Library" << std::endl;
	}

	FT_Face face;
	if (FT_New_Face(ft, "C:\\Windows\\Fonts\\arial.ttf", 0, &face)) {
		std::cout << "ERROR_FREETTYPE: Could not load font" << std::endl;
	}

	FT_Set_Pixel_Sizes(face, 0, 48);

	if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
		std::cout << "ERROR_FREETYPE: Failed to create glyph metrics" << std::endl;
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}

		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);

		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Now store character for later use
		Character character = {
			texture,
			sudo::math::Vector2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			sudo::math::Vector2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};

		// Add to the character map
		Characters.insert(std::pair<GLchar, Character>(c, character));
	}

	// Free the freetype stuff
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	// Enable blend 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Create shader
	graphics::Shader *shader;
	shader = new graphics::Shader("D:\\SudoGameEngine\\Sudo\\SudoCore\\core\\src\\shaders\\font_shader_vertex.txt", "D:\\SudoGameEngine\\Sudo\\SudoCore\\core\\src\\shaders\\font_shader_fragment.txt");
	shader->enable();
	shader->setUniformMatrix4x4("projection", math::Matrix4x4::Orthographic(0, 800, 600, 0, -1, 1));

	// Create buffer
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		RenderText(*shader, "Nigger Faggot", 20, 20, 1, math::Vector3(255, 255, 0));
	}

	glfwTerminate();

	return EXIT_SUCCESS;
}
*/