#include"box_collider2D.h"

#include"entity.h"
#include"transform_component.h"

#include"../systems/settings_system.h"
#include"../debug.h"

#include"../graphics/renderable2d.h"

namespace sudo { namespace ecs {

	BoxCollider2D::BoxCollider2D()
	{
		// Default box collider values 
		m_keepInBounds = false;
	}
	
	void BoxCollider2D::Update(float deltaTime) 
	{
		// Should the box collider be kept inside the bounds of the screen?
		if (m_keepInBounds) {
			// X
			if (m_entityHolder->transform->position.x + m_bounds.x >= m_settingsSystem->GetWindowSize().x) {
				m_entityHolder->transform->position.setX(m_settingsSystem->GetWindowSize().x - m_bounds.x);
			}
			if (m_entityHolder->transform->position.x <= 0) {
				m_entityHolder->transform->position.setX(0);
			}
			// Y
			if (m_entityHolder->transform->position.y + m_bounds.y >= m_settingsSystem->GetWindowSize().y) {
				m_entityHolder->transform->position.setY(m_settingsSystem->GetWindowSize().y - m_bounds.y);
			}
			if (m_entityHolder->transform->position.y <= 0) {
				m_entityHolder->transform->position.setY(0);
			}
		}
	}

	void BoxCollider2D::Start() 
	{
		m_settingsSystem = sudo_system::SettingsSystem::Instance();

		/* Get the Renderable2D component attatched to m_entityHolder */
		for (int i = 0; i < m_entityHolder->GetComponentList().size(); i++) {
			if (dynamic_cast<graphics::Renderable2D*>(m_entityHolder->GetComponentList()[i]) != nullptr) {
				m_entityRenderableComponent = dynamic_cast<graphics::Renderable2D*>(m_entityHolder->GetComponentList()[i]);
				m_origin = math::Vector2(m_entityHolder->transform->position.x, m_entityHolder->transform->position.y);
				m_bounds = m_entityRenderableComponent->GetSize();
			}
		}

		if (m_entityRenderableComponent == nullptr) {
			DEBUG* debug = DEBUG::getInstance();
			debug->printMessage("Error when getting renderable2D component in box_collider.cpp", LogType::Error);
		}
	}

	void BoxCollider2D::dataMatch()
	{
		if (m_origin != math::Vector2(m_entityHolder->transform->position.x, m_entityHolder->transform->position.y)) {
			m_origin = math::Vector2(m_entityHolder->transform->position.x, m_entityHolder->transform->position.y);
		}
		if (m_bounds != m_entityRenderableComponent->GetSize()) {
			m_bounds = m_entityRenderableComponent->GetSize();
		}
	}

	const unsigned char BoxCollider2D::IsPointInside(const math::Vector2 & a_point)
	{
		// Important that the box colliders data is good before we check for collisions
		dataMatch();

		if (a_point.x > m_origin.x && a_point.x < m_origin.x + m_bounds.x) {
			if (a_point.y > m_origin.y && a_point.y < m_origin.y + m_bounds.y) {
				return 1;
			}
		}
		return 0;
	}

	const unsigned char BoxCollider2D::Intersects(BoxCollider2D & a_other)
	{
		// Important that the box colliders data is good before we check for collisions
		dataMatch();
		a_other.dataMatch();

		if ((m_origin.x + m_bounds.x) >= (a_other.GetOrigin().x)) {
			if (m_origin.x <= (a_other.GetOrigin().x + a_other.GetBounds().x)) {
				if ((m_origin.y + m_bounds.y) >= (a_other.GetOrigin().y)) {
					if (m_origin.y <= (a_other.GetOrigin().y + a_other.GetBounds().y)) {
						return true;
					}
				}
			}
		}
		return false;
	}

	void BoxCollider2D::SetKeepInBounds(const bool a_value)
	{
		m_keepInBounds = a_value;
	}

	math::Vector2  BoxCollider2D::GetOrigin()
	{
		return m_origin;
	}
	math::Vector2  BoxCollider2D::GetBounds()
	{
		return m_bounds;
	}
} } 