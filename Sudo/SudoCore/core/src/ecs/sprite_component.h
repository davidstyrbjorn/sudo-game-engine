#pragma once

#include"component.h"
#include"../graphics/renderable2d.h"

namespace sudo { namespace ecs {

	class SpriteComponent : public Component, public graphics::Renderable2D {
	private:

		unsigned int TCBO;
		unsigned int texture;

		char* m_imagePath;

	public:
		/* Constructor */
		SpriteComponent(char* a_imagePath);

		/* Destructor */
		~SpriteComponent();

		/* Component virtual methods */
		void Start()	override;
		void Update()	override { }

		/* Renderable2D virtual methods */
		//std::vector<graphics::VertexData> GetPrimitiveData() { }
	};
	
} } 