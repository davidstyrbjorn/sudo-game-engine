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
			TriangleComponent(math::Vector2 &a_size);

			/* Component class methods */
			void Start()	override;
			void Update()	override { }

			/* Renderable2D class methods */
			void SetPosition(math::Vector3 &a_newPosition)	override;
			void SetScale(math::Vector3 &a_newScale)		override;
			void Scale(float a_magnitude)					override;

			void bind()		override;
			void unbind()	override;

		private:
			unsigned int VBO, VAO, EBO;
		};

	}
}
