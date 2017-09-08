#pragma once

#include"component.h"
#include"../graphics/renderable2d.h"

namespace sudo {
	namespace ecs {

		// Forward decleration
		class Transform;

		class TriangleComponent : public Component, public graphics::Renderable2D {
		public:
			/* Constrcutor */
			TriangleComponent(math::Vector2 &a_size, math::Vector4 &a_color);

			/* Destructor */
			~TriangleComponent();

			/* Component class methods */
			void Start()	override;
			void Update()	override { }

			/* Renderable2D class methods */
			void bind()		override;
			void unbind()	override;

		private:
			/* Data mainly different buffer handles */
			unsigned int VBO, VAO, EBO, CBO;

			/* Method from Renderable2D */
			void resized() override;
		};

	}
}
