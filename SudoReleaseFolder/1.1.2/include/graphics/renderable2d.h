#pragma once

#include"../math/vector2.h"
#include"../math/vector3.h"
#include"../math/vector4.h"
#include"../math/color.h"

#include"../math/math.h"

#include"../definitions.h"

#include<vector>
#include<array>

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
		class Texture;
	}
}

namespace sudo { namespace graphics { 

	struct QuadVertexData 
	{
		math::Vector3 pos;
		math::Color color;
		math::Vector2 uv;
		float tid;

		QuadVertexData(const math::Vector3 &a_pos, const math::Color &a_color, const math::Vector2 &a_uv)
		{
			pos = a_pos;
			color = a_color;
			uv = a_uv;
		}
	};

	struct TriangleVertexData {
		math::Vector3 pos;
		math::Color color;

		TriangleVertexData(const math::Vector3 &a_pos, const math::Color &a_color) 
		{
			pos = a_pos;
			color = a_color;
		}
	};

	/* Base class for 2D renderable shapes */
	class Renderable2D {
	public:
		/* Virtual desctructor */
		virtual ~Renderable2D() { }

		/* Getters */
		inline const math::Vector2 &GetSize() { return m_size; }
		inline math::Color &GetColor() { return m_color; }
		ecs::Transform* GetEntityTransform() { return m_entityTransform; }
		graphics::Texture* GetTexture() { return m_texture; }
		inline const uint8 GetPointCount() { return c_pointCount; }
		virtual std::array<math::Vector3, 4> GetPrimitivePoints() { return {}; };

		/* Sets m_size to a new specified size */
		void SetSize(const math::Vector2 &a_newSize);

		/* Sets m_color to a new color */
		void SetColor(const math::Color &a_newColor);

		/* Scales up m_size by orders of magnitude */
		void SizeUp(const float a_magnitude);

		/* Scales down m_size by orders of magnitude */
		void SizeDown(const float a_magnitude);

		/* Get the renderables texture id, return 0 if ther is no texture on the renderable */
		const uint getTID() const;

	protected:	
		/* Renderable2D shared data */
		ecs::Transform *m_entityTransform;
		math::Vector2 m_size;
		math::Color m_color;
		uint8 c_pointCount; // 8-bit integer

		math::Vector2 m_sizeBeforeReisze;

		// Texture 
		Texture *m_texture;
	};
} }