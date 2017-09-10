#pragma once

#include"../math/vector3.h"
#include"component.h"

namespace sudo { namespace ecs { 

	class Transform : public Component {
	public:
		/* Class Data */
		math::Vector3 position;
		math::Vector3 scale;

		Transform();

		/* Methods */
		void Move(const math::Vector3& a_vector);

		void Start() override;
		void Update() override;
	};

} } 