#include"../../gl_include.h"

#include"text_system.h"

#include"../math/vector2.h"
#include"../math/color.h"
#include"../math/mat4.h"
#include"../math/vector3.h"

#include"../debug.h"

#include"../graphics/shader.h"
#include"../graphics/font.h"

// @ TODO (Default font path)
#if defined(_WIN32)

#endif
#if defined(_APPLE_) && defined(_MACH_)
	#define DEFAULT_FONT_PATH "/Library/Fonts/arial.ttf"
#endif

namespace sudo { namespace sudo_system { 

	TextSystem * TextSystem::_instance = nullptr;

	TextSystem* TextSystem::Instance() 
	{
		if (_instance == nullptr)
			_instance = new TextSystem();
		return _instance;
	}

	void TextSystem::Flush()
	{
		// Bind
		m_shader->enable();
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(VAO);

		// Draw all the text inside the m_textToRender vector
		while (!m_textToRender.empty()) 
		{
			graphics::TextLabel temp = m_textToRender.back();

			// Draw text
			m_shader->setUniform3f("textColor", math::Vector3(temp.r, temp.g, temp.b));

			// Iterate through all characters 
			std::string::const_iterator c;
			for (c = temp.m_textLiteral.begin(); c != temp.m_textLiteral.end(); c++) 
			{
				graphics::GlyphCharacter ch = m_fonts.at(m_currentFont)->m_characters[*c];

				float xpos = temp.x + ch.m_bearings.x;
				float ypos = temp.y - (ch.m_size.y - ch.m_bearings.y);

				float width = ch.m_size.x;
				float height = ch.m_size.y;

				// Update VBO 
				float vertices[6][4] = {
					{ xpos,			ypos + height,   0.0, 0.0 },
					{ xpos,			ypos,			 0.0, 1.0 },
					{ xpos + width, ypos,			 1.0, 1.0 },

					{ xpos,			ypos + height,   0.0, 0.0 },
					{ xpos + width, ypos,			 1.0, 1.0 },
					{ xpos + width, ypos + height,   1.0, 0.0 }
				};
				glBindTexture(GL_TEXTURE_2D, ch.m_textureID);

				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
				
				glDrawArrays(GL_TRIANGLES, 0, 6);

				// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
				temp.x += (ch.offset >> 6); // Bitshift by 6 to get value in pixels (2^6 = 64)
			}

			m_textToRender.pop_back();

			//glBindVertexArray(0);
			//glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	void TextSystem::DrawText(std::string a_string, math::Vector2 a_position, math::Color a_color)
	{
		m_textToRender.push_back(graphics::TextLabel(a_string, a_position.x, a_position.y, a_color.r/255, a_color.g/255, a_color.b/255));
	}

	void TextSystem::LoadFont(const char * a_path, const char* a_fontName)
	{
		// Insert new font with a_fontName
		m_fonts.insert(std::pair<const char*, graphics::Font*>(a_fontName, new graphics::Font(a_path)));
	}

	void TextSystem::SetFont(const char* a_name)
	{
		// Set the local variable so we know what font to use when we render
		m_currentFont = (char*)a_name;
	}

	void TextSystem::Start()
	{
		glewInit();
		glewExperimental = true;

		// Create default font
		m_fonts.insert(std::pair<const char*, graphics::Font*>("default", new graphics::Font("C:\\Windows\\Fonts\\arial.ttf")));
		m_currentFont = "default";

		// Start OpenGL setup
		// Enable OpenGL blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Construct the shader
		m_shader = new graphics::Shader("D:\\SudoGameEngine\\Sudo\\SudoCore\\core\\src\\shaders\\font_shader_vertex.txt", "D:\\SudoGameEngine\\Sudo\\SudoCore\\core\\src\\shaders\\font_shader_fragment.txt");
		m_shader->enable();
		m_shader->setUniformMatrix4x4("projection", math::Matrix4x4::Orthographic(0, 800, 0, 600, -1, 1));

		// Buffer creation 
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void TextSystem::CleanUp()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

	void TextSystem::Update() { }
	void TextSystem::Enable() { }
	void TextSystem::Disable() { }
} } 