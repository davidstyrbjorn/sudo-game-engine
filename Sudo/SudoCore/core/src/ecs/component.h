#pragma once

namespace sudo { namespace ecs {

	typedef enum {
		ACTIVE,
		DISABLED,
		REMOVED
	} ComponentState;

	class Entity;

	class Component
	{
	public:
		/* Virtual Destructor */
		virtual ~Component() { delete m_entityHolder; }
		
		/* Sets the component state */
		void SetComponentState(ComponentState a_newState) { m_componentState = a_newState; }

		/* Returns the state of the component */
		const ComponentState GetComponentState() { return m_componentState; }

		/* Updates the component behaviour */
		virtual void Update() = 0;

		/* Starts, updates the necc behvaiours at start */
		virtual void Start() = 0;

		/* Returns the name of the component */
		const char* GetName() { return m_componentName; }
		
		/* Returns the destroy trigger */
		const unsigned char GetDestroyTrigger() { return m_destroyTrigger; }

		/* Sets the destroy trigger, used when deleting component */
		void SetDestroyTrigger(const bool a_value) { m_destroyTrigger = a_value; }

		/* Sets the entity holder */
		void SetEntityHolder(Entity *a_newHolder) { m_entityHolder = a_newHolder; }

		/* Gets entity holder */
		Entity* GetEntityHolder() { return m_entityHolder; }

	protected:
		ComponentState m_componentState = ComponentState::ACTIVE; // Active by default
		char* m_componentName; // Name of the component
		unsigned char m_destroyTrigger = false;
		Entity *m_entityHolder; // Pointer to the holder of this component
	};

} }