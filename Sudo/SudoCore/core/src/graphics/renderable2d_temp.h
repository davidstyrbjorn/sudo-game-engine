#pragma once

#include"../../sudo.h"

namespace sudo { namespace graphics { 

	struct VertexData {
		math::Vector3 m_position;
		math::Vector4 m_color;
	};

	class Renderable2D_temp {
	private:
		math::Vector3 m_position;
		math::Vector3 m_size;
		math::Vector4 m_color;

		VertexArrayBuffer *m_VAO;
		
	};

}} 