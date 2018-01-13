#pragma once

#include"component.h"
#include"../graphics/renderable2d.h"

namespace sudo {
	namespace math {
		class Vector3;
	}
}

namespace sudo { namespace ecs {

	class SpriteComponent : public Component, public graphics::Renderable2D {
	private:
		char* m_imagePath;

	public:
		/* Constructor */
		SpriteComponent(char* a_imagePath);
		SpriteComponent();

		/* Destructor */
		~SpriteComponent();

		/* Component virtual methods */
		void Start()	override;
		void Update(float deltaTime)	override { }

		// Getters
		// Returns the 4 vertex positions of the sprite
		std::array<math::Vector3, 4> GetPrimitivePoints() override;
		char* GetSpriteImagePath() { return (m_imagePath); }
	};
	
} } 