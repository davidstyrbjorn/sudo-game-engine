#pragma once

#include<iostream>
#include"../sudo_behaviour.h"

namespace sudo { namespace ecs {

	class Entity;

	class Component : public SudoBehaviour
	{
	public:
		/* Virtual Destructor */
		virtual ~Component() {
			//std::cout << "Component Removed" << std::endl;
		}

		// Getters
		const bool IsActive() { return m_isActive; }
		Entity* GetEntityHolder() { return m_entityHolder; }
		
		// Setters
		void SetEntityHolder(Entity *a_newHolder) { m_entityHolder = a_newHolder; }

		// State modification methods
		void Enable() { m_isActive = true; }
		void Disable() { m_isActive = false; }
		void Toggle() { m_isActive = !m_isActive; }

	protected:
		bool m_isActive = true; 
		Entity *m_entityHolder; // Pointer to the holder of this component
	};

} }