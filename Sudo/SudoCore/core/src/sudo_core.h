#pragma once

namespace sudo {
	namespace utility {
		class Timer;
} }

namespace sudo {

	#define PRINT_FPS 0

	// Forward declarations
	namespace graphics {
		class Window;
	}
	namespace sudo_system {
		class InputSystem;
		class WorldSystem;
		class SettingsSystem;
		class SoundSystem;
		class BatchRendererSystem;
		class ParticleSystem;
		class TextSystem;
	}
	namespace math {
		class Vector2;
		class Vector3;
	}
	class SudoClass;
	class CoreSettings;

	class SudoCore {
	private:
		/* ======================================================================= */
		/* ======================> CORE ENGINE DATA <============================= */
		/* ======================================================================= */
		SudoClass *m_engineInstance;
		graphics::Window *m_window;

		/* Systems */
		sudo_system::InputSystem		*m_inputSystem;
		sudo_system::WorldSystem		*m_worldSystem;
		sudo_system::SettingsSystem		*m_settingsSystem;
		sudo_system::SoundSystem		*m_soundSystem;
		sudo_system::BatchRendererSystem *m_batchRenderer;
		sudo_system::ParticleSystem		*m_particleSystem;
		sudo_system::TextSystem			*m_textSystem;

		utility::Timer *timer, *deltaTimer, *fixedUpdateTimer;
#if PRINT_FPS
		utility::Timer *realTimer;
#endif

		/* ======================================================================= */
		/* ======================> CORE ENGINE METHODS <========================== */
		/* ======================================================================= */
		/* Does the necc clean up */
		void clean_up();
		
		/* Runs the game loop */
		void game_loop();
	
	public:		
		/* Destructor */
		~SudoCore() { clean_up(); }

		/* Returns the reference adress to the window object */
		graphics::Window &GetWindow();

		/* takes in all required data and instances the engine */
		void init(math::Vector2 a_windowSize, char* a_windowCaption, SudoClass *a_engineInstance);

		/* Default Constructor */
		SudoCore();
	};

}