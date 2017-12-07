#pragma once

#include"../../definitions.h"
#include"../math/vector2.h"

namespace sudo { namespace graphics {

	// Base class for every character glyph
	struct GlyphCharacter {
		uint m_textureID; // ID handle of glyph texture
		math::Vector2 m_size; // Size of glyph in pixels
		math::Vector2 m_bearings; // Offset from baseline to top of glyph
		uint offset; // Offset in bytes to the next glyph
	};

} }