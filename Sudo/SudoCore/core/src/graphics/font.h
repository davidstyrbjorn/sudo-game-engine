#pragma once

#include<map>
#include<ft2build.h>
#include FT_FREETYPE_H
#include"text_character.h"

namespace sudo { namespace graphics {

	//class GlyphCharacter;

	struct Font 
	{
		FT_Face m_face;
		FT_Library m_lib;
		std::map<char, graphics::GlyphCharacter> m_characters;

		Font(const char* a_path);
	};

} }