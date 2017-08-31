#pragma once

#include<iostream>

#include"component.h"
#include"entity.h"

namespace sudo { namespace ecs { 

	class TestComponent : public Component {
	public:
		TestComponent() {
			m_componentName = "TestComponent";
		}

		void Start() {

		}

		void Update() {

		}

	};

} }
