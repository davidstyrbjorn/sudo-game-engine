#pragma once

#include"component.h"
#include"../graphics/renderable2d.h"

namespace sudo {
	namespace graphics {
		struct VertexData;
} }

namespace sudo {
	namespace ecs {

		// Forward decleration
		class Transform;

		class TriangleComponent : public Component, public graphics::Renderable2D {
		public:
			/* Constrcutor */
			TriangleComponent(math::Vector2 &a_size, math::Color &a_color);

			/* Destructor */
			~TriangleComponent();

			/* Component virtual methods */
			void Start()	override;
			void Update(float deltaTime)	override { }

			/* Renderable2D virtual methods */
			std::vector<graphics::VertexData> GetPrimitiveData();
		};

	}
}