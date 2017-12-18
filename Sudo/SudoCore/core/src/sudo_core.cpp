#include "sudo_core.h"

#include"../sudo.h"
#include"../gl_include.h"
#include"../definitions.h"

namespace sudo { 

SudoCore::SudoCore()
{

}

void SudoCore::init(const math::Vector2 a_windowSize, char* a_windowCaption, SudoClass *a_engineInstance)
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
	m_settingsSystem->SetWindowSize((math::Vector2&)a_windowSize);
	m_settingsSystem->SetBackgroundColor(math::Color(0, 0, 0, 255));
	m_settingsSystem->SetAutoRender(false);
	m_settingsSystem->instancePtr = m_engineInstance;

	/* Input system */
	m_inputSystem = sudo_system::InputSystem::Instance();
	m_inputSystem->Enable();

	/* WorldSystem/ECS System*/
	m_worldSystem = sudo_system::WorldSystem::Instance();
	m_worldSystem->Enable();

	/* Batch Renderer */
	m_batchRenderer = sudo_system::BatchRendererSystem::Instance();
	m_batchRenderer->Enable();

	/* Text system */
	m_textSystem = sudo_system::TextSystem::Instance();
	m_textSystem->Enable();

	/* Particle System */
	m_particleSystem = sudo_system::ParticleSystem::Instance();
	m_particleSystem->Enable();

	/* ========================================= */

	m_textSystem->Start();

	/* User-end stuff, important we call this last after all the init stuff is done! */
	/* Call the Start method for the end-user */
	m_engineInstance->Start();

	/* Call Start on systems */
	m_worldSystem->Start();
	m_batchRenderer->Start();
	m_particleSystem->Start();

	/* Start the game_loop; This means Start gets called before any Update calls */
	game_loop();
}

void SudoCore::clean_up()
{
	/* Call it the instant the window is closed */
	m_engineInstance->OnWindowClose();

	/* This destroys  everything related to the GLFW library */
	glfwTerminate();

	/* Call CleanUp() on all systems */
	m_inputSystem->CleanUp();
	m_worldSystem->CleanUp();
	m_batchRenderer->CleanUp();
	m_settingsSystem->CleanUp();
	m_soundSystem->CleanUp();
	m_particleSystem->CleanUp();
	m_textSystem->CleanUp();

	delete m_window;

	/* After this point everything should be clear */
	m_engineInstance->OnApplicationClose();
}

void SudoCore::game_loop()
{
	timer = new utility::Timer();
	timer->Start();

	deltaTimer = new utility::Timer();
	deltaTimer->Start();
	float _frameStartTime = deltaTimer->GetTicks();

	float _deltaTime = deltaTimer->GetTicks() - _frameStartTime;

#if PRINT_FPS
	realTimer = new utility::Timer;
	realTimer->Start();
	unsigned int framesPerSecond = 0;
#endif

	while (m_window->is_open())
	{
#if PRINT_FPS
		if (realTimer->GetTicks() >= 1000) {
			std::cout << framesPerSecond << std::endl;
			framesPerSecond = 0;
			realTimer->Reset();
		}
#endif
		// Set the time at the start of the frame
		_frameStartTime = deltaTimer->GetTicks();

		// Call the user-end Update methods
		m_engineInstance->Update(_deltaTime);

		// Update the WorldSystem holding all game entities 
		m_worldSystem->Update(_deltaTime);
		// Update particle system
		m_particleSystem->Update(_deltaTime);
		// Update input | Currently only does window shake effect 
		m_inputSystem->Update(_deltaTime);

		if (timer->GetTicks() >= m_settingsSystem->GetMS()) 
		{
			// Clear the screen 
			m_window->clear();

			// Reset renderer data 
			m_batchRenderer->Begin();
			m_particleSystem->Begin();
			m_textSystem->Begin();

			// Call update on renderers
			m_batchRenderer->Update(_deltaTime);

			// System (components)
			m_worldSystem->Render();
			// User end
			m_engineInstance->Render();

			// Render w/OpenGL 
			m_batchRenderer->End();
			m_batchRenderer->Flush();
			m_particleSystem->Flush();
			m_textSystem->Flush();

			// Display the current drawns elements 
			m_window->display();

			// Reset the loop timer
			timer->Reset();
#if PRINT_FPS
			framesPerSecond++;
#endif
		}

		m_worldSystem->LateUpdate(_deltaTime);
		m_engineInstance->LateUpdate(_deltaTime);

		// Calculate the time it took to get this frame done and set it to _deltaTime
		_deltaTime = deltaTimer->GetTicks() - _frameStartTime;
	}

	clean_up();
}

graphics::Window& SudoCore::GetWindow() 
{
	return *m_window;
}

}