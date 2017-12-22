#pragma once

namespace sudo { namespace graphics {

	struct TextLabel {
		TextLabel(std::string a_string, float x, float y, float r, float g, float b) {
			this->m_textLiteral = a_string;
			this->x = x;
			this->y = y;
			this->r = r;
			this->g = g;
			this->b = b;
		}

		std::string m_textLiteral;
		float x, y;
		float r, g, b;
	};
	
} }