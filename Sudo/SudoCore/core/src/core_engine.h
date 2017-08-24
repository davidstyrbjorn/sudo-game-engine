#pragma once

#include"math\vector2.h"

namespace sudo {

	// Forward declarations
	namespace graphics {
		class Window;
	}
	namespace system {
		class InputSystem;
		class WorldSystem;
	}
	class SudoClass;
	class CoreSettings;
	
	
	class CoreEngine {
	private:
		/* ======================================================================= */
		/* ======================> CORE ENGINE DATA <============================= */
		/* ======================================================================= */
		graphics::Window *m_window;
		SudoClass *m_engineInstance;
		system::InputSystem *m_inputSystem;
		system::WorldSystem *m_worldSystem;

		/* ======================================================================= */
		/* ======================> CORE ENGINE METHODS <========================== */
		/* ======================================================================= */
		/* init method is called from constructor */
		/* takes in all necc data to create a engine instance */
		void init(const math::Vector2& a_windowSize, char* a_windowCaption, SudoClass *a_engineInstance);

		/* Does the necc clean up */
		void clean_up();
		
		/* Runs the game loop */
		void game_loop();
	
	public:		
		/* Destructor */
		~CoreEngine() { clean_up(); }

		/* Default Constructor */
		CoreEngine(
			const math::Vector2& a_windowSize, 
			char *a_windowCaption,
			SudoClass *a_engineInstance
		);
	};

}