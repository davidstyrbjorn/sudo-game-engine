#include"box_collider2D.h"
#include"../../sudo.h"

namespace sudo { namespace ecs {

	BoxCollider2D::BoxCollider2D()
	{
		m_componentName = "BoxCollider2D";
	}
	
	void BoxCollider2D::Update() { }

	void BoxCollider2D::Start() 
	{
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

	const unsigned char BoxCollider2D::ContactWith(const BoxCollider2D & a_other)
	{
		return 0;
	}

	const unsigned char BoxCollider2D::IsInside(const BoxCollider2D & a_other)
	{
		return 0;
	}

} } 