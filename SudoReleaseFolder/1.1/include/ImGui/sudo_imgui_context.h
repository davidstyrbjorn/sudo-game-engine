#pragma once

namespace sudo {

	// Forward declerations
	namespace sudo_system {
		class WindowSystem;
		class SettingsSystem;
		class InputSystem;
		class ParticleSystem;
		class SoundSystem;
		class TextSystem;
		class WorldSystem;
		class BatchRendererSystem;
	}
	namespace ecs {
		class Entity;
	}

	namespace debug {
		class SudoImGui {
		public:
			// Constructor
			SudoImGui();

			// The various debug windows/widgets
			void ShowMetricsWindow();
			void ShowEntitiesWindow();
			void ShowSystemsWindow();
			void ShowEntityInspector();
			void ShowSystemWidgets();
			void ShowAddEntityWidget();

			void ClickedOnEntity();

		private:
			sudo_system::WindowSystem *m_windowSystem;
			sudo_system::SettingsSystem *m_settingsSystem;
			sudo_system::InputSystem *m_inputSystem;
			sudo_system::ParticleSystem *m_particleSystem;
			sudo_system::SoundSystem *m_soundSystem;
			sudo_system::TextSystem *m_textSystem;
			sudo_system::WorldSystem *m_worldSystem;
			sudo_system::BatchRendererSystem *m_renderSystem;

			// C++11 thing with direct decleration, can be overriden in constructor!
			bool m_showSystemsWindow = false;
			bool m_showEntityInspector = false;
			bool m_showRendererWidget = false;
			bool m_showParicleWidget = false;
			bool m_showWindoWidget = false;
			bool m_showAddRenderableWidget = false;
			bool m_showAddEntityWidget = false;
			ecs::Entity* m_clickedEntity;
		};
} }