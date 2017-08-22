#include "core_engine.h"

#include"../sudo.h"
#include"../gl_include.h"

namespace sudo{

CoreEngine::CoreEngine(const math::Vector2& a_windowSize, char *a_windowCaption, SudoClass *a_engineInstance)
{
	glewInit();
	glewExperimental = true;

	init(a_windowSize, a_windowCaption, a_engineInstance);
}

void CoreEngine::init(const math::Vector2& a_windowSize, char* a_windowCaption, SudoClass *a_engineInstance)
{
	/* Setting the engine instance */
	m_engineInstance = a_engineInstance;

	/* Create the game window */
	m_window = new graphics::Window(a_windowSize.getX(), a_windowSize.getY(), a_windowCaption);

	/* Sets the corrent GLFW callbacks, if not done InputSystem won't trigger */
	system::InputSystem::EnableInputSystemSystem();

	/* ========================================= */

	/* Print the current version of the engine */
	std::cout << GetSudoVersion() << std::endl;

	/* Call the Start method for the end-user */
	m_engineInstance->Start();

	/* Start the game_loop; This means Start gets called before any Update calls */
	game_loop();
}

void CoreEngine::clean_up()
{
	/* This destroys everything related to the GLFW library */
	glfwTerminate();

	delete m_engineInstance;
	delete m_window;
}

void CoreEngine::game_loop()
{
	while (m_window->is_open()) 
	{
		m_window->clear();

		/* Call the Update method for the end-user s*/
		m_engineInstance->Update();

		m_window->display();
	}
}
}