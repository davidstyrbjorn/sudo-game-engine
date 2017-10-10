#include"renderable2d.h"

namespace sudo { namespace graphics {

	void Renderable2D::SetSize(const math::Vector2 &a_newSize) 
	{
		m_size = a_newSize; 
		this->resized();
	}

	void Renderable2D::SetColor(const math::Vector4 &a_newColor) 
	{ 
		m_color = a_newColor; 
		this->recolored(); 
	}

	void Renderable2D::SizeUp(const float a_magnitude)
	{
		m_sizeBeforeReisze = m_size;
		m_size = math::Vector2(m_size.x + a_magnitude, m_size.y + a_magnitude);

		this->resized();
	}

	void Renderable2D::SizeDown(const float a_magnitude)
	{
		m_sizeBeforeReisze = m_size;
		m_size = math::Vector2(m_size.x - a_magnitude, m_size.y - a_magnitude);
		this->resized();
	}

	void Renderable2D::resized_clamp()
	{
		/* Clamp the size of the renderable2d */
		float x_size = m_size.x;
		float y_size = m_size.y;
		math::ClampFloat(x_size, MAX_PIXEL_SIZE_X, MIN_PIXEL_SIZE_X);
		math::ClampFloat(y_size, MAX_PIXEL_SIZE_Y, MIN_PIXEL_SIZE_Y);

		m_size = math::Vector2(x_size, y_size);
	}
	
} }