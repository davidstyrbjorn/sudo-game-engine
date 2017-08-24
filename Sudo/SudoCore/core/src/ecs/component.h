#pragma once

namespace sudo { namespace ecs {

	class Component
	{
	public:
		/* Virtual Destructor */
		virtual ~Component() { }
		
		/* Activates the component */
		virtual void Activate() { m_isActive = true; }

		/* Disables the component */
		virtual void Disable() { m_isActive = false; }

		/* Updates the component behaviour */
		virtual void Update() = 0;

		/* Starts, updates the necc behvaiours at start */
		virtual void Start() = 0;

		/* Returns the name of the component */
		const char* GetName() { return m_name; }

		/* Returns the state of the component */
		const unsigned char IsActive() { return m_isActive; }
		
		/* Returns the destroy trigger */
		const unsigned char GetDestroyTrigger() { return m_destroyTrigger; }

		/* Sets the destroy trigger, used when deleting component */
		void SetDestroyTrigger(const bool a_value) { m_destroyTrigger = a_value; }

	protected:
		unsigned char m_isActive = true; // Depending on this value update the component behaviours
		char* m_name; // Name of the component
		unsigned char m_destroyTrigger = false;
	};

} }