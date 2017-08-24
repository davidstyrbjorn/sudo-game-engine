#pragma once

#include"component.h"
#include<iostream>

namespace sudo { namespace ecs { 

	class TestComponent : public Component {
	public:
		TestComponent() {
			m_name = "TestComponent";
		}

		int x = 10;

		void Start() {
			std::cout << "TestComponent->Start() = called" << std::endl;
		}

		void Update() {

		}

	};

} }