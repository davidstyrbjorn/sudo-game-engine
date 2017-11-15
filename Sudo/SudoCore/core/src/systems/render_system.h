#pragma once

#include"sudo_system.h"
#include"../graphics/renderable2d.h"
#include<deque>

namespace sudo {
	namespace graphics {
		class Shader;
} }

namespace sudo { namespace sudo_system { 

	class RenderSystem : public SudoSystem {
	private:
		/* Private constructor, singleton class */
		RenderSystem() { }
		static RenderSystem *_instance;

	public:
		/* Method to get pointer to system */
		static RenderSystem *Instance();

		/* Methods from the SudoSystem base class */
		void Enable()	{ m_isActive = true; }
		void Disable()	{ m_isActive = false; }
		void CleanUp()	override;
		void Update()	override;
		void Start()	override;

		/* Adds a_shape to m_renderList to be rendered during next render iteration */
		void Draw(graphics::Renderable2D *a_shape);

	private:
		/* RenderSystem data */
		graphics::Shader *m_shader;
		unsigned char m_isActive;
		std::deque<graphics::Renderable2D*> m_renderList;
	};

} } 