#pragma once

#include"component.h"
#include<iostream>

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
