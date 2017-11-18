#include "sudo_core.h"

#include"../sudo.h"
#include"../gl_include.h"
#include"../definitions.h"

namespace sudo { 

SudoCore::SudoCore()
{

}

void SudoCore::init(const math::Vector2& a_windowSize, char* a_windowCaption, SudoClass *a_engineInstance)
{
	/* Print the current version of the engine */
	std::cout << GetSudoVersion() << std::endl;

	glewInit();
	glewExperimental = true;

	/* Setting the engine instance */
	m_engineInstance = a_engineInstance;

	/* Create the game window */
	m_window = new graphics::Window(a_windowSize.x, a_windowSize.y, a_windowCaption);

	/* ========================================= */
	/*               ENABLE SYSTEMS              */
	/* ========================================= */

	/* Sound System */
	m_soundSystem = sudo_system::SoundSystem::Instance();
	m_soundSystem->Enable();

	/* Settings system */
	m_settingsSystem = sudo_system::SettingsSystem::Instance();
	m_settingsSystem->Enable();
	m_settingsSystem->SetFPS(DEFAULT_FPS_CAP);
	m_settingsSystem->SetWindowSize(a_windowSize);
	m_settingsSystem->SetBackgroundColor(math::Vector4(0, 0, 0, 1));

	/* Input system */
	m_inputSystem = sudo_system::InputSystem::Instance();
	m_inputSystem->Enable();

	/* WorldSystem/ECS System*/
	m_worldSystem = sudo_system::WorldSystem::Instance();
	m_worldSystem->Enable();

	/* Render System */
	//m_renderSystem = sudo_system::RenderSystem::Instance();
	//m_renderSystem->Enable();

	/* /2 Batch Renderer */
	m_batchRenderer = sudo_system::BatchRendererSystem::Instance();
	m_batchRenderer->Enable();

	/* ========================================= */

	/* User-end stuff, important we call this last after all the init stuff is done! */
	/* Call the Start method for the end-user */
	m_engineInstance->Start();

	/* Call Start on systems */
	m_worldSystem->Start();
	//m_renderSystem->Start();
	m_batchRenderer->Start();

	timer = new utility::Timer();
	timer->Start();

	/* Start the game_loop; This means Start gets called before any Update calls */
	game_loop();
}

void SudoCore::clean_up()
{
	/* This destroys  everything related to the GLFW library */
	glfwTerminate();

	/* Call CleanUp() on all systems */
	m_inputSystem->CleanUp();
	m_worldSystem->CleanUp();
	m_renderSystem->CleanUp();
	m_batchRenderer->CleanUp();
	m_settingsSystem->CleanUp();
	m_soundSystem->CleanUp();

	delete m_engineInstance;
	delete m_window;
}

void SudoCore::game_loop()
{
	while (m_window->is_open()) 
	{
		/* Limit the update rate */
		if (timer->GetTicks() >= m_settingsSystem->GetMS()) 
		{
			m_batchRenderer->Begin();

			/* Swap buffers and clear the screen */
			m_window->clear();

			/* Update the WorldSystem holding all game entities */
			m_worldSystem->Update();

			/* Call the Update method for the end-user */
			m_engineInstance->Update();

			m_inputSystem->Update();

			/* Render w/OpenGL */
			m_batchRenderer->Flush();
			//m_renderSystem->Update();

			/* Display the current drawns elements */
			m_window->display();

			timer->Reset();
		}
	}
}

graphics::Window& SudoCore::GetWindow() 
{
	return *m_window;
}

}