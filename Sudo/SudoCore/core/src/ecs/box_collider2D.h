#pragma once

#pragma once

#include"../math/vector2.h"
#include"component.h"

namespace sudo {
	namespace graphics {
		class Renderable2D;
	}
	namespace system {
		class SettingsSystem;
	}
}

namespace sudo { namespace ecs {

	class BoxCollider2D : public Component {
	private:
		// <===========> PRIVATE DATA <===========> //
		math::Vector2 m_origin, m_bounds;
		graphics::Renderable2D *m_entityRenderableComponent;

		bool m_keepInBounds;
		system::SettingsSystem *m_settingsSystem;

		void dataMatch();

	public:
		/* Constructor */
		BoxCollider2D();

		// <===========> COMPONENT BASE METHODS <===========> //
		void Update() override;
		void Start() override;

		// <===========> BOX COLLIDER METHODS <===========> //
		/* Returns true if a_point is located inside this bounding box */
		const unsigned char IsPointInside(const math::Vector2 &a_point);

		/* Returns true is this bounding box is in contact with a_other */
		const unsigned char Intersects(BoxCollider2D &a_other);

		/* Sets m_keepInBounds */
		void SetKeepInBounds(const bool a_value);

		/* Getters */
		math::Vector2 GetOrigin();
		math::Vector2 GetBounds();
	};
} }