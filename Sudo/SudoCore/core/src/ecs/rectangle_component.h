#pragma once

#include"component.h"
#include"../graphics/renderable2d.h"

namespace sudo {
	namespace graphics {
		struct VertexData;
	}
}

namespace sudo { namespace ecs {

	// Forward decleration
	class Transform;

	class RectangleComponent : public Component, public graphics::Renderable2D {
	public:
		/* Constrcutor */
		RectangleComponent(math::Vector2 &a_size, math::Vector4 &a_color);

		/* Destructor */
		~RectangleComponent();

		/* Component virtual methods */
		void Start()	override;
		void Update(float deltaTime)	override { }

		/* Renderable2D virtual methods */
		std::vector<graphics::VertexData> GetPrimitiveData();
	};
	
} }
