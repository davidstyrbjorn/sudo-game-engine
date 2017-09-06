#pragma once

#include"../math/vector2.h"
#include"../math/vector3.h"
#include"../math/vector4.h"

// Forward decleration
namespace sudo { 
	namespace ecs {
		class Transform;
	}
} 

namespace sudo { namespace graphics { 

	/* Base class for 2D renderable shapes */

	class Renderable2D {
	public:
		/* Virtual desctructor */
		virtual ~Renderable2D() { }

		/* Binds and unbinds the necce buffers when rendering */
		virtual void bind() = 0;
		virtual void unbind() = 0;

		/* Getters */
		inline const ecs::Transform *GetEntityTransform() { return m_entityTransform; }
		inline const math::Vector2 &GetSize() { return m_size; }
		inline const math::Vector4 &GetColor() { return m_color; }

		/* Setters */
		void SetSize(const math::Vector2 &a_newSize) { m_size = a_newSize; }
		void SetColor(const math::Vector4 &a_newColor) { m_color = a_newColor; }

	protected:	
		/* Renderable2D shared data */
		ecs::Transform *m_entityTransform;		
		math::Vector2 m_size;
		math::Vector4 m_color;
	};
} }