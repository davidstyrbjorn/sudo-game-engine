#pragma once

#include"../math/vector2.h"
#include"../math/vector3.h"
#include"../math/vector4.h"

#include"../math/math.h"

#include"../../definitions.h"

#include<vector>

// Texture 
#include"texture.h"

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
		/*
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
		// Texture
		//float tid;
		*/		

		math::Vector3 pos;
		math::Vector4 color;
		math::Vector2 uv;
		float tid;

		VertexData(const math::Vector3 &a_pos, const math::Vector4 &a_color, const math::Vector2 &a_uv)
		{
			pos = a_pos;
			color = a_color;
			uv = a_uv;
		}
	};

	/* Base class for 2D renderable shapes */
	class Renderable2D {
	public:
		/* Virtual desctructor */
		virtual ~Renderable2D() { }

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

		/* Constructs a vertex list for the renderer to use */
		virtual std::vector<graphics::VertexData> GetPrimitiveData() { std::vector<graphics::VertexData> temp; return temp; }

		inline const uint getTID() const { return m_texture == nullptr ? 0 : m_texture->getID(); }

	protected:	
		/* Renderable2D shared data */
		ecs::Transform *m_entityTransform;
		math::Vector2 m_size;
		math::Vector4 m_color;

		math::Vector2 m_sizeBeforeReisze;

		// Texture 
		Texture *m_texture;

	public:
		sudo::RenderableType m_type;
	};
} }