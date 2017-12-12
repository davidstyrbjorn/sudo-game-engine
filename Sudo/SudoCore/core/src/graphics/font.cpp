#include "font.h"

#include"../../gl_include.h"

#include"../debug.h"

#include"../math/vector2.h"

namespace sudo { namespace graphics {

	Font::Font(const char * a_path, const int a_size)
	{
		// Glew
		glewInit();
		glewExperimental = true;

		if (FT_Init_FreeType(&m_lib)) {
			DEBUG::getInstance()->printMessage("Failed to init FreeType library", LogType::Error);
		}

		if (FT_New_Face(m_lib, a_path, 0, &m_face)) {
			DEBUG::getInstance()->printMessage("Failed to init FreeType face", LogType::Error);
		}

		FT_Set_Pixel_Sizes(m_face, 0, a_size);

		// Disables byte sized alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// Fill the m_character map
		for (GLubyte c = 0; c < 128; c++) {
			// Load the charcter glyph
			if (FT_Load_Char(m_face, c, FT_LOAD_RENDER)) {
				DEBUG::getInstance()->printMessage("Failejklöjklsdd to load FreeType character glyph", LogType::Error);
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

	}

	void Font::SetFontSize(const int a_size)
	{
		FT_Set_Pixel_Sizes(m_face, 0, a_size);
	}
	
}}
