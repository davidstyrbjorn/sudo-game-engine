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
	m_settingsSystem->SetWindowSize((math::Vector2&)a_windowSize);
	m_settingsSystem->SetBackgroundColor(math::Vector4(0, 0, 0, 1));

	/* Input system */
	m_inputSystem = sudo_system::InputSystem::Instance();
	m_inputSystem->Enable();

	/* WorldSystem/ECS System*/
	m_worldSystem = sudo_system::WorldSystem::Instance();
	m_worldSystem->Enable();

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
	m_batchRenderer->CleanUp();
	m_settingsSystem->CleanUp();
	m_soundSystem->CleanUp();

	delete m_window;

	m_engineInstance->OnApplicationQuit();
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
		if (realTimer->GetTicks() > 1000) {
			std::cout << framesPerSecond << std::endl;
			framesPerSecond = 0;
			realTimer->Reset();
		}
		#endif

		// Set the time at the start of the frame
		_frameStartTime = deltaTimer->GetTicks();

		// Swap buffers and clear the screen 
		m_window->clear();

		// Reset renderer data 
		m_batchRenderer->Begin();

		// Call the Update method for the end-user 
		if(_deltaTime == 0) m_engineInstance->Update(1.0f);
		else				m_engineInstance->Update(_deltaTime);
		if (timer->GetTicks() >= FIXED_UPDATE_MS) {
			m_engineInstance->FixedUpdate();
			timer->Reset();
		}

		// Update the WorldSystem holding all game entities 
		m_worldSystem->Update(_deltaTime);

		// Render w/OpenGL 
		m_batchRenderer->End();
		m_batchRenderer->Flush();

		// Display the current drawns elements 
		m_window->display();

		// Update input | Currently only does window shake effect 
		m_inputSystem->Update();

		// Calculate the time it took to get this frame done and set it to _deltaTime
		_deltaTime = deltaTimer->GetTicks() - _frameStartTime;

		#if PRINT_FPS
		framesPerSecond++;
		#endif
	}

	clean_up();
}

graphics::Window& SudoCore::GetWindow() 
{
	return *m_window;
}

}