#include"../../gl_include.h"

#include"text_system.h"

#include"../math/vector2.h"
#include"../math/color.h"
#include"../math/mat4.h"
#include"../math/vector3.h"

#include"../debug.h"

#include"../graphics/shader.h"

#if defined(_WIN32)

#endif
#if defined(_APPLE_) && defined(_MACH_)
	#define DEFAULT_FONT_PATH "/Library/Fonts/arial.ttf"
#endif

namespace sudo { namespace sudo_system { 

	struct Font {
		FT_Face m_face;
		std::map<char, graphics::GlyphCharacter> m_characters;

		Font(const char* a_path, FT_Library *a_ftLib) 
		{
			if (FT_Init_FreeType(a_ftLib)) {
				DEBUG::getInstance()->printMessage("Failed to init FreeType library", LogType::Error);
			}

			if (FT_New_Face(*a_ftLib, a_path, 0, &m_face)) {
				DEBUG::getInstance()->printMessage("Failed to init FreeType face", LogType::Error);
			}

			FT_Set_Pixel_Sizes(m_face, 0, 48);

			// Fill the m_character map
			for (GLubyte c = 0; c < 128; c++) {
				// Load the charcter glyph
				if (FT_Load_Char(m_face, c, FT_LOAD_RENDER)) {
					DEBUG::getInstance()->printMessage("Failed to load FreeType character glyph", LogType::Error);
					continue;
				}

				// Generate texture
				GLuint texture;
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, m_face->glyph->bitmap.buffer);
				// Set texture options
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				// Create the glyph struct and store it
				graphics::GlyphCharacter character = {
					texture,
					math::Vector2(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows),
					math::Vector2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top),
					m_face->glyph->advance.x
				};
				m_characters.insert(std::pair<char, graphics::GlyphCharacter>(c, character));
			}

			FT_Done_Face(m_face);
			FT_Done_FreeType(*a_ftLib);
		}
	};

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
			for (c = temp.m_textLiteral.begin(); c != temp.m_textLiteral.end(); c++) {
				graphics::GlyphCharacter ch = m_characters[*c];

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

	void TextSystem::LoadFont(const char * a_path, int a_index)
	{
		m_fonts.insert(std::pair<int, Font*>(1, new Font(a_path, &m_ftLib)));
	}

	void TextSystem::SetFont(int a_index)
	{
		if (FT_Init_FreeType(&m_ftLib)) {
			DEBUG::getInstance()->printMessage("Failed to init FreeType library", LogType::Error);
		}
		//FT_Set_Pixel_Sizes(m_fonts.at(1)->m_face, 0, 90);
	}

	void TextSystem::Update() 
	{

	}

	void TextSystem::Start()
	{
		glewInit();
		glewExperimental = true;

		// Initalize everything
		if (FT_Init_FreeType(&m_ftLib)) {
			DEBUG::getInstance()->printMessage("Failed to init FreeType library", LogType::Error);
		}

		if (FT_New_Face(m_ftLib, "C:\\Windows\\Fonts\\comicbd.ttf", 0, &m_ftFace)) {
			DEBUG::getInstance()->printMessage("Failed to init FreeType face", LogType::Error);
		}

		// 0 width will set the width dynamic
		FT_Set_Pixel_Sizes(m_ftFace, 0, 90);

		if (FT_Load_Char(m_ftFace, 'X', FT_LOAD_RENDER)) {
			DEBUG::getInstance()->printMessage("Failed to create FreeType charcter glyph", LogType::Error);
		}

		// Disables byte sized alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// Fill the m_character map
		for (GLubyte c = 0; c < 128; c++) {
			// Load the charcter glyph
			if (FT_Load_Char(m_ftFace, c, FT_LOAD_RENDER)) {
				DEBUG::getInstance()->printMessage("Failed to load FreeType character glyph", LogType::Error);
				continue;
			}

			// Generate texture
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_ftFace->glyph->bitmap.width, m_ftFace->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, m_ftFace->glyph->bitmap.buffer);
			// Set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Create the glyph struct and store it
			graphics::GlyphCharacter character = {
				texture,
				math::Vector2(m_ftFace->glyph->bitmap.width, m_ftFace->glyph->bitmap.rows),
				math::Vector2(m_ftFace->glyph->bitmap_left, m_ftFace->glyph->bitmap_top),
				m_ftFace->glyph->advance.x
			};
			m_characters.insert(std::pair<char, graphics::GlyphCharacter>(c, character));
		}

		FT_Done_Face(m_ftFace);
		FT_Done_FreeType(m_ftLib);

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

	void TextSystem::Enable() { }

	void TextSystem::Disable() { }

	void TextSystem::CleanUp()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

} } 