#pragma once

#include"sudo_system.h"
#include"../sudo_behaviour.h"

#include"../graphics/renderer_base.h"
#include"../definitions.h"
#include<vector>

namespace sudo {
	namespace graphics {
		class Shader;
		class IndexBuffer;
		class VertexArrayBuffer;
		class Renderable2D;
		class Texture;

		struct QuadVertexData;
		struct TriangleVertexData;
	}
	namespace sudo_system {
		class WorldSystem;
		class SettingsSystem;
	}
}

namespace sudo { namespace sudo_system { 

// Renderer pre-processor data
#define MAX_PRIMITIVES 2000
#define QUAD_VERTEX_SIZE sizeof(graphics::QuadVertexData)
#define TRIANGLE_VERTEX_SIZE sizeof(graphics::TriangleVertexData)

#define QUAD_SIZE QUAD_VERTEX_SIZE * 4
#define QUAD_BUFFER_SIZE QUAD_SIZE * MAX_PRIMITIVES 
#define INDICES_COUNT MAX_PRIMITIVES * 6

#define TRIANGLE_SIZE TRIANGLE_VERTEX_SIZE * 3
#define TRIANGLE_BUFFER_SIZE TRIANGLE_SIZE * MAX_PRIMITIVES

	class BatchRendererSystem : public SudoSystem, public graphics::RendererBase, public SudoBehaviour {
	private:
		// Private constructor 
		BatchRendererSystem();
		static BatchRendererSystem *_instance;

	public:
		// Singleton connection
		static BatchRendererSystem *Instance();

		// Method from SudoSystem base class 
		void Enable() { m_isActive = true; }
		void Disable() { m_isActive = false; }
		void CleanUp() override;

		// SudoBehaviour 
		void Update(float deltaTime) override;
		void Start() override;
			
		// Renderer routines
		void Begin() override;
		void Submit(graphics::Renderable2D *a_primitive, graphics::Renderable2D *a_primitive2 = nullptr, graphics::Renderable2D *a_primitive3 = nullptr);
		void _Submit(graphics::Renderable2D *a_primitive);
		void Flush() override;
		void End() override;

	private:
		// Batch Renderer data 
		uint m_quadVAO, m_triangleVAO;
		graphics::Shader *m_shader;

		graphics::QuadVertexData *m_mapBuffer;
		graphics::IndexBuffer *m_indexBuffer;
		uint m_quadVBO, m_triangleVBO;

		// Texture 
		std::vector<uint> m_textureSlots;

		// System references
		SettingsSystem *m_settingsSystem;
		WorldSystem *m_worldSystem;

		bool m_isActive;
		unsigned short int m_quadCount, m_triangleCount;
	};

} } 