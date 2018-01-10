#pragma once

#include"sudo_system.h"
#include"../sudo_behaviour.h"

#include<vector>
#include<map>

#include"../graphics/text_label.h"
#include"../graphics/text_character.h"
#include"../graphics/renderer_base.h"

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

	class TextSystem : public SudoSystem, public graphics::RendererBase, public SudoBehaviour {
	private:
		// Private constructor since this is a singleton class
		TextSystem() { }

		// Static instance of class (only instance)
		static TextSystem *_instance;

	public:
		static TextSystem *Instance();

		// SudoBehaviour
		void Update(float deltaTime) override { }
		void Start() override;

		// Methods from the SudoSystem base class 
		void Enable() override { m_isActive = true; }
		void Disable() override { m_isActive = false; }
		void CleanUp() override;
		bool IsActive() override { return m_isActive; }
		void Toggle() override { m_isActive = !m_isActive; }

		// Render routines
		void Begin() override { };
		void End() override { };
		void Flush() override;

		// Method called by user 
		void DrawText(std::string a_string, math::Vector2 a_position, math::Color a_color);
		void LoadFont(const char* a_path, const char* a_fontName, const int a_size);
		void SetFont(const char* a_name, const int a_size = -1);	
	
	private:
		bool m_isActive;
		std::map<char, graphics::GlyphCharacter> m_characters;
		std::vector<graphics::TextLabel> m_textToRender;
		graphics::Shader *m_shader;
		char* m_currentFont;
		unsigned int VAO, VBO;
		std::map<const char*, graphics::Font*> m_fonts;
	};

} } 