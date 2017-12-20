#pragma once

#include<vector>
#include<type_traits>

namespace sudo { namespace graphics { 

	class Renderable2D;

} } 

namespace sudo { namespace ecs {

	class Component;
	class Transform;

	class Entity {
	private:
		std::vector<Component*> m_components;
		bool m_isActive;
		bool m_removeMe;
		unsigned char m_id;

	public:
		Transform *transform;

	public:
		// Constructor
		Entity() : m_id(0) { init(); }
		Entity(const unsigned char a_id) : m_id(a_id) { init(); }
		void init();

		// Destructor 
		~Entity();

		// Behaviour methods
		void Update(float deltaTime);
		void LateUpdate(float deltaTime);
		void Render();
		void Start();
		void Awake();

		// Component methods
		Component* AddComponent(Component *a_component);
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
		graphics::Renderable2D *GetRenderableComponent() const;
		const std::vector<Component*> GetComponentList() { return m_components; }

		// State handling methods
		inline void Disable() { m_isActive = false; }
		inline void Enable() { m_isActive = true; }
		inline bool IsActive() { return m_isActive; }
		inline void Destroy() { m_removeMe = true; }
		inline bool DestroyMe() { return m_removeMe; }

		// Getters 
		const unsigned char GetID() { return m_id; }
	};
	
} }