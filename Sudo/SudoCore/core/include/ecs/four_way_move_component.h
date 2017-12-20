#pragma once

#include"component.h"

namespace sudo {
	namespace math {
		class Vector2;
	}
	namespace sudo_system {
		class InputSystem;
	}
}

namespace sudo { namespace ecs { 

	class Transform;

	class FourWayMoveComponent : public Component {
	public:
		/* Constructor */
		FourWayMoveComponent(math::Vector2& a_moveSpeed, char* a_up, char* a_down, char* a_right, char* a_left);

		/* Destructor */
		~FourWayMoveComponent();

		/* Component virtual methods */
		void Start() override;
		void Update(float deltaTime) override;

	private:
		// Component data
		float m_xSpeed, m_ySpeed;
		Transform* m_transform;
		char *m_up, *m_down, *m_right, *m_left;
		sudo_system::InputSystem *m_inputSystem;
	};

} } 