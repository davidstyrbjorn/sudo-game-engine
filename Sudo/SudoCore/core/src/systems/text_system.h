#pragma once

#include"sudo_system.h"
#include<ft2build.h>
#include FT_FREETYPE_H

// Forward declerations
namespace sudo {
	namespace math {
		class Vector2;
		class Color;
	}
}

namespace sudo { namespace sudo_system { 

	struct Font {
		FT_Face face;
	};

	class TextSystem : SudoSystem {
	private:
		// Private constructor since this is a singleton class
		TextSystem();

		// Static instance of class (only instance)
		static TextSystem *_instance;

	public:
		static TextSystem *Instance();

		/* Methods from the SudoSystem base class */
		void Update() override;
		void Start() override;
		void Enable() override;
		void Disable() override;
		void CleanUp() override;

		/* Method called by user */
		void DrawText(const math::Vector2 &a_position, const math::Color& a_color, const char* a_string);
	};

} } 