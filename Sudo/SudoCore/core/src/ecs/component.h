#pragma once

#include<iostream>

namespace sudo { namespace ecs {

	typedef enum {
		ACTIVE,
		DISABLED,
	} ComponentState;

	class Entity;

	class Component
	{
	public:
		/* Virtual Destructor */
		virtual ~Component() { 
			std::cout << "Component Removed" << std::endl;
		}
		
		/* Updates the component behaviour */
		virtual void Update() = 0;

		/* Starts, updates the necc behvaiours at start */
		virtual void Start() = 0;

		/* Sets the component state */
		void SetComponentState(ComponentState a_newState) { m_componentState = a_newState; }

		/* Returns the state of the component */
		const ComponentState GetComponentState() { return m_componentState; }

		/* Returns the name of the component */
		const char* GetName() { return m_componentName; }

		/* Sets the entity holder */
		void SetEntityHolder(Entity *a_newHolder) { m_entityHolder = a_newHolder; }

		/* Gets entity holder */
		Entity* GetEntityHolder() { return m_entityHolder; }

	protected:
		ComponentState m_componentState = ComponentState::ACTIVE; // Active by default
		char* m_componentName; // Name of the component
		Entity *m_entityHolder; // Pointer to the holder of this component
	};

} }