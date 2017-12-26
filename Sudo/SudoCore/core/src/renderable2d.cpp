#include"../include/graphics/renderable2d.h"

#include"../include/graphics/texture.h"

namespace sudo { namespace graphics {

	void Renderable2D::SetSize(const math::Vector2 &a_newSize)
	{
		m_size = a_newSize; 
	}

	void Renderable2D::SetColor(const math::Color &a_newColor) 
	{ 
		m_color = a_newColor; 
	}

	void Renderable2D::SizeUp(const float a_magnitude)
	{
		m_sizeBeforeReisze = m_size;
		m_size = math::Vector2(m_size.x + a_magnitude, m_size.y + a_magnitude);
	}

	void Renderable2D::SizeDown(const float a_magnitude)
	{
		m_sizeBeforeReisze = m_size;
		m_size = math::Vector2(m_size.x - a_magnitude, m_size.y - a_magnitude);
	}

	const uint Renderable2D::getTID() const
	{
		return m_texture == nullptr ? 0 : m_texture->getID();
	}
	
} }