#include "../include/sudo_core.h"

#include"../include/sudo.h"
#include"../include/gl_include.h"
#include"../include/definitions.h"

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

	// ENABLE SYSTEMS              
	
	/* Create the game window */
	//m_window = new graphics::Window(a_windowSize.x, a_windowSize.y, a_windowCaption);
	m_windowSystem = sudo_system::WindowSystem::Instance();
	m_windowSystem->Enable();
	m_windowSystem->Init(a_windowSize.x, a_windowSize.y, a_windowCaption);

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
	m_windowSystem->Start();
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
	m_windowSystem->CleanUp();
	m_inputSystem->CleanUp();
	m_worldSystem->CleanUp();
	m_batchRenderer->CleanUp();
	m_settingsSystem->CleanUp();
	m_soundSystem->CleanUp();
	m_particleSystem->CleanUp();
	m_textSystem->CleanUp();

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

	realTimer = new utility::Timer;
	realTimer->Start();
	unsigned int framesPerSecond = 0;

	while (m_windowSystem->IsOpen())
	{
		if (realTimer->GetTicks() >= 1000) {
#if PRINT_FPS
			std::cout << framesPerSecond << std::endl;
#endif
			m_settingsSystem->SetCurrentFPS(framesPerSecond);

			framesPerSecond = 0;
			realTimer->Reset();
		}

		// Set the time at the start of the frame
		_frameStartTime = deltaTimer->GetTicks();

		// Call the user-end Update methods
		m_engineInstance->Update(_deltaTime);

		// Update the window 
		m_windowSystem->Update(_deltaTime);
		// Update the WorldSystem holding all game entities 
		m_worldSystem->Update(_deltaTime);
		// Update particle system
		m_particleSystem->Update(_deltaTime);
		// Update input | Currently only does window shake effect 
		m_inputSystem->Update(_deltaTime);

		if (timer->GetTicks() >= m_settingsSystem->GetMS()) 
		{
			// Clear the screen 
			m_windowSystem->Clear();

			// OpenGL calls here
			m_particleSystem->Begin();
			m_batchRenderer->Begin();
			m_textSystem->Begin();
			
			// Call update on renderers
			m_batchRenderer->Update(_deltaTime);
			
			// User end -> void Render() { }
			m_worldSystem->Render(); // Components
			m_engineInstance->Render(); // Instance class
			
			// Pre rendering, OpenGL calls here
			m_batchRenderer->PrepareTriangle();
			m_batchRenderer->PrepareQuad();
			
			// OpenGL calls here
			m_batchRenderer->End();
			m_particleSystem->End();
			m_textSystem->End();
			
			m_batchRenderer->Flush();
			m_particleSystem->Flush();
			m_textSystem->Flush();

			// Display the current drawns elements 
			m_windowSystem->Display();

			// Reset the loop timer
			timer->Reset();

			framesPerSecond++;
		}

		m_worldSystem->LateUpdate(_deltaTime);
		m_engineInstance->LateUpdate(_deltaTime);

		// Calculate the time it took to get this frame done and set it to _deltaTime
		_deltaTime = deltaTimer->GetTicks() - _frameStartTime;
		m_settingsSystem->SetCurrentMS(_deltaTime);
	}

	clean_up();
}

}