#pragma once

#include"sudo_system.h"

#include<vector>
#include<map>

#include<ft2build.h>
#include FT_FREETYPE_H

#include"../graphics/text_label.h"
#include"../graphics/text_character.h"

// Forward declerations
namespace sudo {
	namespace math {
		class Vector2;
		class Color;
	}
	namespace graphics {
		class Shader;
		class Font;
	}
}

namespace sudo { namespace sudo_system { 

	class TextSystem : SudoSystem {
	private:
		// Private constructor since this is a singleton class
		TextSystem() { }

		// Static instance of class (only instance)
		static TextSystem *_instance;

	public:
		static TextSystem *Instance();

		// Methods from the SudoSystem base class 
		void Update() override;
		void Start() override;
		void Enable() override;
		void Disable() override;
		void CleanUp() override;

		// Render routines
		void Flush();

		// Method called by user 
		void DrawText(std::string a_string, math::Vector2 a_position, math::Color a_color);
		void LoadFont(const char* a_path, const char* a_fontName, const int a_size);
		void SetFont(const char* a_name, const int a_size = -1);	
	
	private:
		std::map<char, graphics::GlyphCharacter> m_characters;
		std::vector<graphics::TextLabel> m_textToRender;
		graphics::Shader *m_shader;
		char* m_currentFont;

		unsigned int VAO, VBO;

		std::map<const char*, graphics::Font*> m_fonts;
	};

} } 