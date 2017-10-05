#pragma once

#include"math\vector2.h"
#include"math\vector3.h"
#include"utility\timer.h"

namespace sudo {

	// Forward declarations
	namespace graphics {
		class Window;
	}
	namespace sudo_system {
		class InputSystem;
		class WorldSystem;
		class RenderSystem;
		class SettingsSystem;
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
		sudo_system::RenderSystem	*m_renderSystem;
		sudo_system::SettingsSystem	*m_settingsSystem;

		utility::Timer *timer;

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
		void init(const math::Vector2& a_windowSize, char* a_windowCaption, SudoClass *a_engineInstance);

		/* Default Constructor */
		SudoCore(
		);
	};

}