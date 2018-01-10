#pragma once

#include<map>

#include"text_character.h"
#include"../definitions.h"

struct FT_Face;
struct FT_Library;

namespace sudo { namespace graphics {

	//class GlyphCharacter;

	struct Font 
	{
		// Members
		FT_Face *m_face;
		FT_Library *m_lib;
		std::map<char, graphics::GlyphCharacter> m_characters;
		uint m_fontSize;

		// Constructor
		Font(const char* a_path, const int a_size);

		// Methods
		void SetFontSize(const int a_size);
	};

} }