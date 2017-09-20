#pragma once

#include"component.h"
#include"../graphics/renderable2d.h"

namespace sudo {
	namespace math {
		class Vector2;
} }

namespace sudo { namespace ecs {

	class SpriteComponent : public Component, public graphics::Renderable2D {
	private:
		graphics::VertexArrayBuffer *m_vertexArray;
		graphics::VertexBuffer *m_vertexBuffer;
		graphics::Buffer *m_elementBuffer;

		unsigned int TCBO;
		unsigned int texture;

		char* m_imagePath;

		/* Method from Renderable2D base */
		void resized() override { } 
		void recolored() override { }

	public:
		/* Constructor */
		SpriteComponent(char* a_imagePath, math::Vector2 &a_size);

		/* Destructor */
		~SpriteComponent();

		/* Component class methods */
		void Start()	override;
		void Update()	override { }

		/* Renderable2D class methods */
		void bind()		override;
		void unbind()	override;

	};
	
} } 