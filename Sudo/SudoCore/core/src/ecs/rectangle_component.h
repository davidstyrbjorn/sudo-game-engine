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
		void SetPosition(math::Vector2 &a_newPosition);
		void SetScale(math::Vector2 &a_newScale);
		void Scale(float a_magnitude);
		void Move(math::Vector2 &a_direction, float a_magnitude);

	private:
		Transform *m_entityTransform;
	};
	
} }
