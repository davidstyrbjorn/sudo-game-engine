#pragma once

#include"../math/vector2.h"
#include"../math/vector3.h"
#include"../math/vector4.h"

#include"../math/math.h"

#include"../../definitions.h"

// Forward decleration
namespace sudo { 
	namespace ecs {
		class Transform;
	}
} 

namespace sudo {
	namespace graphics {
		class VertexArrayBuffer;
		class VertexBuffer;
		class Buffer;
	}
}

namespace sudo { namespace graphics { 

	struct VertexData 
	{
		VertexData(const math::Vector3 &a_pos, const math::Vector4 &a_color, const math::Vector2 &a_uv)
		{
			// Position
			pos[0] = a_pos.x;
			pos[1] = a_pos.y;
			pos[2] = a_pos.z;

			// Colour
			color[0] = a_color.x;
			color[1] = a_color.y;
			color[2] = a_color.z;
			color[3] = a_color.w;

			// UV Coordinates
			uvCoord[0] = a_uv.x;
			uvCoord[1] = a_uv.y;
		}
		float pos[3];
		float color[4];
		float uvCoord[2];
	};

	/* Base class for 2D renderable shapes */
	class Renderable2D {
	public:
		/* Virtual desctructor */
		virtual ~Renderable2D() { }

		/* Binds and unbinds the necce buffers when rendering */
		virtual void bind() = 0;
		virtual void unbind() = 0;

		/* Getters */
		inline const math::Vector2 &GetSize() { return m_size; }
		inline const math::Vector4 &GetColor() { return m_color; }
		ecs::Transform* GetEntityTransform() { return m_entityTransform; }

		/* Sets m_size to a new specified size */
		void SetSize(const math::Vector2 &a_newSize);

		/* Sets m_color to a new color */
		void SetColor(const math::Vector4 &a_newColor);

		/* Scales up m_size by orders of magnitude */
		void SizeUp(const float a_magnitude);

		/* Scales down m_size by orders of magnitude */
		void SizeDown(const float a_magnitude);

	protected:	
		/* Renderable2D shared data */
		ecs::Transform *m_entityTransform;
		math::Vector2 m_size;
		math::Vector4 m_color;

		math::Vector2 m_sizeBeforeReisze;

		/* Private Methods */
		void resized_clamp();
		virtual void resized() = 0;
		virtual void recolored() = 0;

	public:
		sudo::RenderableType m_type;
	};
} }