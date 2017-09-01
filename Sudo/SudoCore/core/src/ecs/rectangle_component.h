#pragma once

#include"component.h"
#include"../graphics/renderable2d.h"

namespace sudo { namespace ecs {

	// Forward decleration
	class Transform;

	class RectangleComponent : public Component, public graphics::Renderable2D {
	public:
		/* Constrcutor */
		RectangleComponent();

		/* Component class methods */
		void Start() override;
		void Update() override;

		/* Renderable2D class methods */
		void SetPosition(math::Vector3 &a_newPosition)						override;
		void SetScale(math::Vector3 &a_newScale)							override;
		void Scale(float a_magnitude)										override;
		void Move(math::Vector3 &a_direction, float a_magnitude)			override;

	private:
		unsigned int VBO;
		unsigned int width, height;
	};
	
} }
