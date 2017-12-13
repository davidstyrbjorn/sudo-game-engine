#pragma once

#include<vector>
#include<type_traits>

namespace sudo { namespace ecs {

	class Component;
	class Transform;

	class Entity {
	private:
		std::vector<Component*> m_components;  
		bool m_isActive;
		bool m_removeMe;

	public:
		Transform *transform;

	public:
		/* Entity Constructor */
		Entity();

		/* Entity Destructor */
		~Entity();

		/* Updates all components inside m_components list */
		void Update(float deltaTime);

		/* Calls start on all components inside m_components list */
		void Start();

		/* Same as start but gets called regardless of state */
		void Awake();

		/* Adds a_component to the components list */
		Component* AddComponent(Component *a_component);

		// class sudo::ecs::class_name
		/* Returns the component inside the components list with a_name */
		template<typename TemplateClass>
		TemplateClass* GetComponent()
		{			
			// Look for component
			for (unsigned int i = 0; i < m_components.size(); ++i) 
			{
				if (typeid(*m_components[i]).name() == typeid(TemplateClass).name())
				{
					// We found the component at index i inside the list
					return static_cast<TemplateClass*>(m_components[i]);
				}
			}

			return nullptr;
		}

		/* Getter for this->components */
		const std::vector<Component*> GetComponentList() { return m_components; }

		/* State methods (m_isActive) */
		__forceinline void Disable()   { m_isActive = false; }
		__forceinline void Enable()	   { m_isActive = true;  }
		__forceinline bool IsActive()  { return m_isActive; }

		__forceinline void Destroy()   { m_removeMe = true; }
		__forceinline bool DestroyMe() { return m_removeMe; }
	};
	
} }