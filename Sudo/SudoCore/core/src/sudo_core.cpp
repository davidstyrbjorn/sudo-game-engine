#pragma once

#include "../include/sudo_core.h"

#include"../include/sudo.h"
#include"../include/definitions.h"

#include<SerializerAPI.h>
#include<sstream>

// OpenAL include guards
#include<al.h>
#include<alc.h>

// Glew include guards
#define GLEW_STATIC
#include"GL\glew.h"

// GLFW inclde guards
#include"GLFW\glfw3.h"

#define STR(x) std::to_string(x)

namespace sudo { 

SudoCore::SudoCore()
{
	// Test read from a level text file
	nano::OpenInputFile("level.txt");
	std::string levelString;
	nano::GetAllFileContent(levelString);
	nano::CloseInputFile();

	std::istringstream levelStream(levelString);
	std::string word;
	while (std::getline(levelStream, word)) 
	{
		if (word == "[ ENTITY ]") 
		{
			// Get the entity name
			std::string entityName;
			std::getline(levelStream, entityName);
			entityName = entityName.substr(7, entityName.length());

			// Instantiate entity with entity name
			ecs::Entity* entity = new ecs::Entity(entityName);

			// Transform data of the entity
			math::Vector2 pos;
			float angle;
			std::string posString, angleString;
			std::vector<std::string> segmentedPosString;
			
			std::getline(levelStream, posString);
			std::getline(levelStream, angleString);
			posString = posString.substr(6, posString.length());
			angleString = angleString.substr(8, angleString.length());
			// angleString is good but posString looks like 0.00, 0.00 so we have to segment the string
			std::stringstream _sps(posString);
			std::string segment;
			while (std::getline(_sps, segment, ',')) { segmentedPosString.push_back(segment); }
			// [0] should be x pos and [1] should be y pos

			// Now the string is setup for being converted
			pos.x = std::stof(segmentedPosString[0]);
			pos.y = std::stof(segmentedPosString[1]);
			angle = std::stof(angleString);

			// Apply the transform data to the instantiated entity
			entity->transform->position = math::Vector3(pos.x, pos.y, 0);
			entity->transform->angle = angle;

			// Component time
			std::string _componentHeader;
			std::getline(levelStream, _componentHeader);
			if(_componentHeader == "[ COMPONENTS ]")
			{
				std::string _componentName;
				std::getline(levelStream, _componentName);
				std::cout << _componentName << std::endl;

				if (_componentName == "RectangleComponent") {
					math::Vector2 size;
					math::Color color;

					// Size
					std::string sizeString;
					std::vector<std::string> segmentedSizeString;
					std::getline(levelStream, sizeString);
					sizeString = sizeString.substr(7, sizeString.length());
					std::stringstream sizeStream(sizeString);
						
					std::string sizeSegment;
					while(std::getline(sizeStream, sizeSegment, ',')) { segmentedSizeString.push_back(sizeSegment); }

					// Color
					std::string colorString;
					std::vector<std::string> segmentedColorString;
					std::getline(levelStream, colorString);
					colorString = colorString.substr(8, colorString.length());
					std::stringstream colorStream(colorString);

					std::string colorSegment;
					while (std::getline(colorStream, colorSegment, ',')) { segmentedColorString.push_back(colorSegment); }

					// Apply the data and add component
					size.x = std::stof(segmentedSizeString[0]);
					size.y = std::stof(segmentedSizeString[1]);
					color.r = std::stof(segmentedColorString[0]);
					color.g = std::stof(segmentedColorString[1]);
					color.b = std::stof(segmentedColorString[2]);
					color.a = std::stof(segmentedColorString[3]);
					entity->AddComponent(new ecs::RectangleComponent(size, color));
				}
			}
		}
	}
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
	m_settingsSystem->SetRenderMode(sudo_system::SudoRenderMode::NORMAL);
	m_settingsSystem->ShowDebugOverlay(false);

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
	// Test for serializing all the data from the world_system singleton
	//nano::OpenOutputFile("level.txt", nano::OpenMode::TRUNCATE);
	//
	//nano::WriteToFile("[ START ]", true);
	//
	//nano::WriteToFile("[ ENTITIES_START]\n", true);
	//for (ecs::Entity* entity : m_worldSystem->GetEntityList()) 
	//{
	//	// Transform
	//	float _x = std::floor(entity->transform->position.x * 100.) / 100.;
	//	float _y = std::floor(entity->transform->position.y * 100.) / 100.;
	//	float _angle = std::floor(entity->transform->angle * 100.) / 100.;
	//
	//	nano::WriteToFile("[ ENTITY ]", true);
	//	nano::WriteToFile("name = " + entity->GetID(), true);
	//	nano::WriteToFile("pos = (" + STR(_x) + ", " + STR(_y) + ")", true);
	//	nano::WriteToFile("angle = " + std::to_string(_angle), true);
	//
	//	// Components
	//	nano::WriteToFile("[ COMPONENTS ]", true);
	//	// Serialize components
	//	for (ecs::Component* component : entity->GetComponentList()) {
	//		// Renderable2D Component
	//		graphics::Renderable2D* renderableComponent = dynamic_cast<graphics::Renderable2D*>(component);
	//		if (renderableComponent != nullptr) {
	//			// Rectangle component
	//			if (renderableComponent->GetTexture() == nullptr) {
	//				nano::WriteToFile("RectangleComponent:", true);
	//
	//				// Rectangle data
	//				math::Vector2 size = renderableComponent->GetSize();
	//				math::Color color = renderableComponent->GetColor();
	//				nano::WriteToFile("size = (" + STR(size.x) + "," + STR(size.y) + ")", true);
	//				nano::WriteToFile("color = (" + STR(color.r) + "," + STR(color.g) + "," + STR(color.b) + "," + STR(color.a) + ")", true);
	//			}
	//			// Sprite Component
	//			else {
	//				nano::WriteToFile("SpriteComponent", true);
	//				
	//				// Sprite data
	//				math::Vector2 size = renderableComponent->GetSize();
	//				math::Color color = renderableComponent->GetColor();
	//				nano::WriteToFile("size = (" + STR(size.x) + "," + STR(size.y) + ")", true);
	//				nano::WriteToFile("color = (" + STR(color.r) + "," + STR(color.g) + "," + STR(color.b) + "," + STR(color.a) + ")", true);
	//
	//				std::string imagePath = renderableComponent->GetTexture()->getImagePath();
	//				nano::WriteToFile("image = " + imagePath, true);
	//			}
	//		}
	//	}
	//
	//	nano::InsertBlankLine();
	//}
	//nano::WriteToFile("\n[ ENTITIES_END ]", true);
	//
	//nano::WriteToFile("[ END ]", true);
	//
	//nano::CloseOutputFile();

	/* Call it the instant the window is closed */
	m_engineInstance->OnWindowClose();

	/* This destroys everything related to the GLFW library */
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

		// Update the internal window system
		m_windowSystem->Update(_deltaTime);
		// Update the internal WorldSystem holding all game entities 
		m_worldSystem->Update(_deltaTime);
		// Update particle system
		m_particleSystem->Update(_deltaTime);
		// Update input internal system
		m_inputSystem->Update(_deltaTime);

		// Render loop 
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