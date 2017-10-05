#include"box_collider2D.h"
#include"../../sudo.h"

namespace sudo { namespace ecs {

	BoxCollider2D::BoxCollider2D()
	{
		m_componentName = "BoxCollider2D";

		// Default box collider values 
		m_keepInBounds = false;
	}
	
	void BoxCollider2D::Update() 
	{
		// Should the box collider be kept inside the bounds of the screen?
		if (m_keepInBounds) {
			// X
			if (m_entityHolder->transform->position.getX() + m_bounds.getX() >= m_settingsSystem->GetWindowSize().getX()) {
				m_entityHolder->transform->position.setX(m_settingsSystem->GetWindowSize().getX() - m_bounds.getX());
			}
			if (m_entityHolder->transform->position.getX() <= 0) {
				m_entityHolder->transform->position.setX(0);
			}
			// Y
			if (m_entityHolder->transform->position.getY() + m_bounds.getY() >= m_settingsSystem->GetWindowSize().getY()) {
				m_entityHolder->transform->position.setY(m_settingsSystem->GetWindowSize().getY() - m_bounds.getY());
			}
			if (m_entityHolder->transform->position.getY() <= 0) {
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

				m_origin = math::Vector2(m_entityHolder->transform->position.getX(), m_entityHolder->transform->position.getY());
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
		if (m_origin != math::Vector2(m_entityHolder->transform->position.getX(), m_entityHolder->transform->position.getY())) {
			m_origin = math::Vector2(m_entityHolder->transform->position.getX(), m_entityHolder->transform->position.getY());
		}
		if (m_bounds != m_entityRenderableComponent->GetSize()) {
			m_bounds = m_entityRenderableComponent->GetSize();
		}
	}

	const unsigned char BoxCollider2D::IsPointInside(const math::Vector2 & a_point)
	{
		// Important that the box colliders data is good before we check for collisions
		dataMatch();

		if (a_point.getX() > m_origin.getX() && a_point.getX() < m_origin.getX() + m_bounds.getX()) {
			if (a_point.getY() > m_origin.getY() && a_point.getY() < m_origin.getY() + m_bounds.getY()) {
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

		if ((m_origin.getX() + m_bounds.getX()) >= (a_other.GetOrigin().getX())) {
			if (m_origin.getX() <= (a_other.GetOrigin().getX() + a_other.GetBounds().getX())) {
				if ((m_origin.getY() + m_bounds.getY()) >= (a_other.GetOrigin().getY())) {
					if (m_origin.getY() <= (a_other.GetOrigin().getY() + a_other.GetBounds().getY())) {
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