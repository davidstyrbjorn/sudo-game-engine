#include "core_engine.h"

#include"../sudo.h"
#include"../gl_include.h"

namespace sudo{

SudoCore::SudoCore(const math::Vector2& a_windowSize, char *a_windowCaption, SudoClass *a_engineInstance)
{
	glewInit();
	glewExperimental = true;

	init(a_windowSize, a_windowCaption, a_engineInstance);
}

void SudoCore::init(const math::Vector2& a_windowSize, char* a_windowCaption, SudoClass *a_engineInstance)
{
	/* Setting the engine instance */
	m_engineInstance = a_engineInstance;

	/* Create the game window */
	m_window = new graphics::Window(a_windowSize.getX(), a_windowSize.getY(), a_windowCaption);

	/* ========================================= */
	/*               ENABLE SYSTEMS              */
	/* ========================================= */
	/* Sets the corrent GLFW callbacks, if not done InputSystem won't trigger */
	m_inputSystem = system::InputSystem::Instance();
	m_inputSystem->Enable();

	/* WorldSystem/ECS System*/
	m_worldSystem = system::WorldSystem::Instance();
	m_worldSystem->Enable();

	/* ========================================= */

	/* Print the current version of the engine */
	std::cout << GetSudoVersion() << std::endl;

	/* Call Start on systems */
	m_worldSystem->Start();

	/* User-end stuff, important we call this last after all the init stuff is done! */
	/* Call the Start method for the end-user */
	m_engineInstance->Start();

	/* Start the game_loop; This means Start gets called before any Update calls */
	game_loop();
}

void SudoCore::clean_up()
{
	/* This destroys everything related to the GLFW library */
	glfwTerminate();

	/* Call CleanUp() on all systems */
	m_inputSystem->CleanUp();
	m_worldSystem->CleanUp();

	delete m_engineInstance;
	delete m_window;
}

void SudoCore::game_loop()
{
	while (m_window->is_open()) 
	{
		m_window->clear();

		/* Update the WorldSystem holding all game entities */
		m_worldSystem->Update();

		/* Call the Update method for the end-user */
		m_engineInstance->Update();

		m_window->display();
	}
}
}