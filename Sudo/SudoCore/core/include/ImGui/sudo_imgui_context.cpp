#include "sudo_imgui_context.h"

#include"imgui.h"
#include"imgui_glfw.h"

// All SudoSystems
#include"../systems/settings_system.h"
#include"../systems/input_system.h"
#include"../systems/particle_system.h"
#include"../systems/sound_system.h"
#include"../systems/text_system.h"
#include"../systems/world_system.h"
#include"../systems/batch_render_system.h"
#include"../systems/window_system.h"

#include"../ecs/transform_component.h"
#include"../ecs/four_way_move_component.h"
#include"../ecs/box_collider2D.h"
#include"../ecs/sound_component.h"
#include"../ecs/sprite_component.h"
#include"../ecs/rectangle_component.h"

#include"../graphics/renderable2d.h"
#include"../graphics/texture.h"
#include"../math/color.h"
#include"../math/vector2.h"

//#include"../sound/sound_include.h"
#include"../sound/sound_source.h"

#include<string>
#include<vector>

#include"../ecs/entity.h"

// Taken from imgui_demo.cpp!
#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))

namespace sudo { namespace debug { 

SudoImGui::SudoImGui() 
{
	m_windowSystem = sudo_system::WindowSystem::Instance();
	m_settingsSystem = sudo_system::SettingsSystem::Instance();
	m_inputSystem = sudo_system::InputSystem::Instance();
	m_particleSystem = sudo_system::ParticleSystem::Instance();
	m_soundSystem = sudo_system::SoundSystem::Instance();
	m_textSystem = sudo_system::TextSystem::Instance();
	m_worldSystem = sudo_system::WorldSystem::Instance();
	m_renderSystem = sudo_system::BatchRendererSystem::Instance();
}

void SudoImGui::ShowMetricsWindow()
{
	ImGui::SetNextWindowPos(ImVec2(5, 5));
	ImGui::Begin("Sudo Debug", false, ImVec2(200, 150), 0.7f,
		ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | 
		ImGuiWindowFlags_::ImGuiWindowFlags_NoMove | 
		ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse
	);

	// Basic metrics
	std::string ms = "MS: " + std::to_string(m_settingsSystem->GetCurrentMS());
	ImGui::Text(ms.c_str());
	std::string fps = "FPS: " + std::to_string(m_settingsSystem->GetCurrentFPS());
	ImGui::Text(fps.c_str());

	// Window toggle buttons
	if(ImGui::Button("Show Systems")) {
		m_showSystemsWindow = !m_showSystemsWindow;
	}
	if (ImGui::Button("Show Window")) {

	}

	ImGui::End();
}

void SudoImGui::ShowEntitiesWindow() 
{
	ImGui::SetNextWindowPos(ImVec2(5, 160));
	ImGui::Begin("Sudo Entities", false, ImVec2(200, 150), 0.7f, 
		ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_::ImGuiWindowFlags_NoMove
	);

	std::vector<ecs::Entity*> entityList = sudo_system::WorldSystem::Instance()->GetEntityList();

	ImGui::Text("Entity List");
	ImGui::Columns(2, "columns2", true);
	ImGui::SetColumnOffset(1, 70);
	for (int i = 0; i < entityList.size(); i++) 
	{
		if (!entityList[i]->DestroyMe()) 
		{
			std::string button = std::string(entityList[i]->GetID()) + "##" + std::to_string(i);
			//std::string button = "s";
			if (ImGui::Button(button.c_str()))
			{
				m_clickedEntity = entityList[i];
				m_showEntityInspector = true;
			}
			ImGui::NextColumn();
		}
	}

	ImGui::Separator();

	std::string temp = "Count: " + std::to_string(entityList.size());
	ImGui::Text(temp.c_str());

	ImGui::End();
}

void SudoImGui::ShowSystemWidgets()
{
	if (m_showRendererWidget) 
	{
		ImGui::Begin("Renderer", &m_showRendererWidget, ImVec2(250, 200), 0.9f, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);

		ImGui::Text("Metrics");

		ImGui::Text("MS: 0.0"); // @
		std::string vertexCount = "No. Vertices: " + std::to_string(m_renderSystem->GetVertexCount());
		ImGui::Text(vertexCount.c_str());

		ImGui::Separator();

		ImGui::Text("Blending");
		if (ImGui::Button("Enable##blend")) {
			m_renderSystem->EnableBlend();
		}
		ImGui::SameLine(60);
		if (ImGui::Button("Disable##blend")) {
			m_renderSystem->DisableBlend();
		}

		ImGui::Separator();

		ImGui::Text("Wireframe Mode");
		if (ImGui::Button("Enable##wireframe")) {
			m_settingsSystem->SetRenderMode(sudo_system::SudoRenderMode::WIRE_FRAME_MODE);
		}
		ImGui::SameLine(60);
		if (ImGui::Button("Disable##wireframe")) {
			m_settingsSystem->SetRenderMode(sudo_system::SudoRenderMode::NORMAL);
		}

		ImGui::End();
	}

	if (m_showParicleWidget)
	{
		ImGui::Begin("Particles", &m_showParicleWidget, ImVec2(300, 325), 0.9f, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);

		// Spawn Particles
		static int count = 0;

		static ImVec2 position = ImVec2(0, 0);
		static ImVec2 size = ImVec2(4, 4);

		static bool randomColor = false;
		static ImVec4 color = ImVec4(1, 0, 0, 1);
		static bool doFade = false;

		static ImVec2 velocity = ImVec2(0, 0);
		static bool randomVelocity = false;
		static float randomVelocityMagnitude = 1;

		static float lifetime = 1000; // 1 second default

		static bool doGravity = false;
		static float gravityScale = PARTICLE_GRAVITY_Y;

		// Number of particles to spawn
		ImGui::SliderInt("Count", &count, 0, MAX_PARTICLES);
		if (ImGui::IsItemHovered()) {
			ImGui::BeginTooltip();
			ImGui::Text("Number of particles created when you click on spawn");
			ImGui::EndTooltip();
		}

		ImGui::Separator();
		
		// Position and size
		ImGui::InputFloat2("Position", (float*)&position, 1);
		ImGui::InputFloat2("Size", (float*)&size, 1);

		ImGui::Checkbox("Random Color", &randomColor);
		if(!randomColor) ImGui::ColorEdit4("Color", (float*)&color);
		ImGui::Checkbox("Color Fade", &doFade);

		ImGui::Separator();

		// Velocity of the particle
		ImGui::Checkbox("Random Velocity", &randomVelocity);
		if (!randomVelocity) ImGui::InputFloat2("Velocity", (float*)&velocity, 3);
		if (randomVelocity)  ImGui::InputFloat("Magnitude", &randomVelocityMagnitude, 0, 0, 3);

		ImGui::Separator();

		// Particle lifetime
		ImGui::InputFloat("Lifetime", &lifetime);

		ImGui::Separator();

		// Gravity 
		ImGui::Checkbox("Gravity Simulated", &doGravity);
		if (doGravity) ImGui::InputFloat("Gravity Scale", &gravityScale, 0, 0, 4);

		static bool hasPressed = false;

		if (ImGui::Button("Spawn")) {
			if (!hasPressed) {
				hasPressed = true;

				sudo_system::ParticleConfiguration x;
				x.DoFade = doFade;
				x.GravityScale = gravityScale;
				x.GravitySimulated = doGravity;
				
				math::Vector3 spawnPos = math::Vector3(position.x, position.y, 0);
				math::Vector2 spawnSize = math::Vector2(size.x, size.y);
				math::Color spawnColor = math::Color::Red();
				if (randomColor)
					spawnColor = math::Color::GetRandomColor();
				else
					math::Color spawnColor = math::Color(color.x, color.y, color.z, color.w)*255;
				math::Vector2 spawnVelocity = math::Vector2(0, 0);
				if (randomVelocity)
					spawnVelocity = math::Vector2::GetRandomVector(-randomVelocityMagnitude, randomVelocityMagnitude);
				else
					spawnVelocity = math::Vector2(velocity.x, velocity.y);
				float spawnLifetime = lifetime;

				// Spawn particles!
				for (int i = 0; i < count; i++) 
				{
					if (randomVelocity)
						spawnVelocity = math::Vector2::GetRandomVector(-randomVelocityMagnitude, randomVelocityMagnitude);

					m_particleSystem->Submit(spawnPos, spawnSize, spawnColor, spawnLifetime, spawnVelocity, x);
				}
			}
		}
		else {
			hasPressed = false;
		}

		ImGui::End();
	}

	if (m_showWindoWidget)
	{
		ImGui::Begin("Window", &m_showWindoWidget, ImVec2(250, 300), 0.9f);



		ImGui::End();
	}
}

void SudoImGui::ShowSystemsWindow()
{
	if (m_showSystemsWindow) 
	{
		ImGui::SetNextWindowSize(ImVec2(200, 200));

		ImGui::Begin("Sudo Systems", &m_showSystemsWindow, 
			ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_::ImGuiWindowFlags_NoMove
		);
		/*
		../systems/settings_system.h <- This one shouldn't be fucked with!
		../systems/window_system.h
		../systems/input_system.h
		../systems/particle_system.h
		../systems/sound_system.h
		../systems/text_system.h
		../systems/world_system.h
		../systems/batch_render_system.h
		*/
		// List all the asshole-systems
		if (m_windowSystem->IsActive())	ImGui::TextColored(ImVec4(0, 255, 0, 255), "Window System");
		else							ImGui::TextColored(ImVec4(255, 0, 0, 255), "Window System");
		if (ImGui::IsItemClicked(0))
		{
			// Show Window system widget
			m_showWindoWidget = !m_showWindoWidget;
		}
		ImGui::SameLine(125);
		if (ImGui::Button("Toggle##0")) {
			m_windowSystem->Toggle();
		}

		if(m_inputSystem->IsActive())	ImGui::TextColored(ImVec4(0,255,0,255),    "Input System");
		else							ImGui::TextColored(ImVec4(255, 0, 0, 255), "Input System");
		ImGui::SameLine(125);
		if (ImGui::Button("Toggle##2")) {
			m_inputSystem->Toggle();
		}

		if (m_renderSystem->IsActive()) ImGui::TextColored(ImVec4(0, 255, 0, 255), "Render System");
		else						    ImGui::TextColored(ImVec4(255, 0, 0, 255), "Render System");
		if (ImGui::IsItemClicked(0))
		{
			// Show Render system widget
			m_showRendererWidget = !m_showRendererWidget;
		}
		ImGui::SameLine(125);
		if (ImGui::Button("Toggle##1")) {
			m_renderSystem->Toggle();
		}

		if (m_particleSystem->IsActive()) ImGui::TextColored(ImVec4(0, 255, 0, 255), "Particle System");
		else						      ImGui::TextColored(ImVec4(255, 0, 0, 255), "Particle System");
		if (ImGui::IsItemClicked(0))
		{
			// Show Particle system widget
			m_showParicleWidget = !m_showParicleWidget;
		}
		ImGui::SameLine(125);
		if (ImGui::Button("Toggle##3")) {
			m_particleSystem->Toggle();
		}

		if (m_soundSystem->IsActive())  ImGui::TextColored(ImVec4(0, 255, 0, 255), "Sound System");
		else						    ImGui::TextColored(ImVec4(255, 0, 0, 255), "Sound System");
		ImGui::SameLine(125);
		if (ImGui::Button("Toggle##4")) {
			m_soundSystem->Toggle();
		}

		if (m_textSystem->IsActive())  ImGui::TextColored(ImVec4(0, 255, 0, 255), "Text System");
		else						   ImGui::TextColored(ImVec4(255, 0, 0, 255), "Text System");
		ImGui::SameLine(125);
		if (ImGui::Button("Toggle##5")) {
			m_textSystem->Toggle();
		}

		if (m_worldSystem->IsActive()) ImGui::TextColored(ImVec4(0, 255, 0, 255), "World System");
		else						   ImGui::TextColored(ImVec4(255, 0, 0, 255), "World System");
		ImGui::SameLine(125);
		if (ImGui::Button("Toggle##6")) {
			m_worldSystem->Toggle();
		}

		ImGui::End();
	}
}

void SudoImGui::ShowEntityInspector()
{
	if (m_showEntityInspector && !m_clickedEntity->DestroyMe()) 
	{
		ImGui::Begin("Entity Inspector", &m_showEntityInspector, ImVec2(300,450), 0.8f);

		// Core value
		std::string id = "ID: " + std::string(m_clickedEntity->GetID());
		ImGui::Text(id.c_str());

		ImGui::Separator(); ImGui::Spacing();

		// Active state text
		bool _ia = m_clickedEntity->IsActive();
		ImGui::Checkbox("Active", &_ia);
		if (_ia) m_clickedEntity->Enable();
		else	 m_clickedEntity->Disable();
		// State Modification buttons
		if (ImGui::Button("Destroy")) {
			m_clickedEntity->Destroy();
			m_showEntityInspector = false;
		}

		ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();

		// Transform Component 
		if (ImGui::CollapsingHeader("Transform")) {
			ImGui::Text("Position");
			ImGui::PushItemWidth(70);
			ImGui::InputFloat("X", &m_clickedEntity->transform->position.x, 0, 0, 2);
			ImGui::SameLine(102);
			ImGui::InputFloat("Y", &m_clickedEntity->transform->position.y, 0, 0, 2);
			ImGui::SameLine(95*2);
			ImGui::InputFloat("Z", &m_clickedEntity->transform->position.z, 0, 0, 2);
			ImGui::PopItemWidth();

			ImGui::InputFloat("Rotation", &m_clickedEntity->transform->angle, 1.0f, 1.0f, 1);
		}

		// Renderable Component
		auto renderable = m_clickedEntity->GetRenderableComponent();
		bool hasRenderable = renderable == nullptr ? false : true;
		if (hasRenderable && ImGui::CollapsingHeader("Renderable"))
		{
			ImGui::Text("Renderable Component: true");

			ImGui::Separator(); 

			// Size
			ImGui::Text("Size");
			float _x = renderable->GetSize().x;
			float _y = renderable->GetSize().y;
			ImGui::SliderFloat("Width", &_x, 0, m_settingsSystem->GetWindowSize().x, "%0.0f");
			ImGui::SliderFloat("Height", &_y, 0, m_settingsSystem->GetWindowSize().y, "%0.0f");
			renderable->SetSize(math::Vector2(_x, _y));

			ImGui::Separator();

			// Color
			ImGui::Text("Color");
			ImVec4 color = ImColor(renderable->GetColor().r / 255, renderable->GetColor().g / 255, renderable->GetColor().b / 255, renderable->GetColor().a / 255);
			ImGui::ColorEdit4("Renderable Color", (float*)&color);
			renderable->SetColor(math::Color(color.x * 255, color.y * 255, color.z * 255, color.w * 255));

			ImGui::Separator();

			// Texture
			auto _txtre = renderable->GetTexture();
			if (_txtre != nullptr) {
				ImGui::Text("Texture: true");

				std::string _imagePath = std::string(_txtre->getImagePath());
				int _index = _imagePath.find_last_of("\\")+1;
				std::string _imageName = "Name: ";
				for (int i = _index; i < _imagePath.length(); ++i) {
					_imageName.append(1, _imagePath.at(i));
				}
				ImGui::Text(_imageName.c_str());

				std::string imagePath = "Location: " + std::string(_txtre->getImagePath());
				ImGui::Text(imagePath.c_str());

				static char newImage[128] = "";
				ImGui::InputText("New Image", newImage, 128);
				if (ImGui::Button("Load")) {
					_txtre->loadImage(newImage);
				}

				ImGui::Separator();

				// Display the image
				ImGui::Text("Texture");
				int new_width = (int)(_txtre->getWidth() / 4);
				int new_height = (int)(_txtre->getHeight() / 4);
				ImGui::Image((void*)_txtre->getID(), ImVec2(new_width, new_height));
			}
			else {
				ImGui::Text("Texture: nullptr");
			}
		}

		// BoxCollider2D component
		// Check if entity has boxcollider2d component
		auto _bc2d = m_clickedEntity->GetComponent<ecs::BoxCollider2D>();
		bool hasBC2D = (_bc2d == nullptr) ? false : true;
		if (hasBC2D && ImGui::CollapsingHeader("BoxCollider2D")) {
			ImGui::Text("BoxCollider2D Component: true");

			ImGui::Separator(); 

			ImVec2 bc_origin = ImVec2(_bc2d->GetOrigin().x, _bc2d->GetOrigin().y);
			ImGui::InputFloat2("Origin", (float*)&bc_origin, 1);

			ImVec2 bc_bounds = ImVec2(_bc2d->GetBounds().x, _bc2d->GetBounds().y);
			ImGui::InputFloat2("Bounds", (float*)&bc_bounds, 1);
		}

		auto _sc = m_clickedEntity->GetComponent<ecs::SoundComponent>();
		bool hasSC = (_sc == nullptr) ? false : true;
		// Sound Component
		if (hasSC && ImGui::CollapsingHeader("SoundComponent")) {
			ImGui::Text("Sound Component: true");

			ImGui::Separator(); 

			// List all of the sounds on the component
			std::map<const char*, ecs::SoundStruct*> soundMap = _sc->GetSoundList();
			int soundCount = 0;
			for (auto const& x : soundMap) 
			{
				// Sound index and name
				if (ImGui::CollapsingHeader(std::to_string(soundCount).c_str())) {
					std::string sound1 = "Sound Name: " + std::string(x.first);
					ImGui::Text(sound1.c_str());

					// Sound state buttons
					std::string play = "Play##" + std::to_string(soundCount);
					if (ImGui::Button(play.c_str())) {
						x.second->soundSource->play(true);
					}
					ImGui::SameLine(50);
					std::string pause = "Pause##" + std::to_string(soundCount);
					if (ImGui::Button(pause.c_str())) {
						x.second->soundSource->pause();
					}
					ImGui::SameLine(100);
					std::string stop = "Stop##" + std::to_string(soundCount);
					if (ImGui::Button(stop.c_str())) {
						x.second->soundSource->stop();
					}

					ImGui::Separator();

					// Other sound values
					float volume = x.second->soundSource->getVolume();
					float pitch = x.second->soundSource->getPitch();
					bool isLooping = x.second->soundSource->isLooping();

					ImGui::SliderFloat("Volume", &volume, 0, 1);
					ImGui::SliderFloat("Pitch", &pitch, 0, 10);
					ImGui::Checkbox("Looping", &isLooping);

					x.second->soundSource->setVolume(volume);
					x.second->soundSource->setPitch(pitch);
					x.second->soundSource->setLooping(isLooping);
				}
				soundCount++;
			}
		}

		// Four-way move component
		ecs::FourWayMoveComponent* _fwm = m_clickedEntity->GetComponent<ecs::FourWayMoveComponent>();
		bool hasMove = (_fwm == nullptr) ? false : true;
		if (hasMove && ImGui::CollapsingHeader("Four-way Move")) {
			// Velocity
			ImVec2 fwm_velocity = ImVec2(_fwm->GetVelocity().x, _fwm->GetVelocity().y);

			//ImGui::SliderFloat2("Velocity", (float*)&fwm_velocity, 0, 10);
			ImGui::InputFloat2("Velocity", (float*)&fwm_velocity);

			_fwm->SetVelocity(math::Vector2(fwm_velocity.x, fwm_velocity.y));

			ImGui::Separator();

			// Keys
			std::string fwm_up = "Up: " + std::string(_fwm->GetKeys("up"));
			std::string fwm_down = "Down: " + std::string(_fwm->GetKeys("down"));
			std::string fwm_right = "Right: " + std::string(_fwm->GetKeys("right"));
			std::string fwm_left = "Left: " + std::string(_fwm->GetKeys("left"));

			ImGui::Text("Move Keys");
			ImGui::Text(fwm_up.c_str());
			ImGui::Text(fwm_down.c_str());
			ImGui::Text(fwm_right.c_str());
			ImGui::Text(fwm_left.c_str());
		}
		
		// Add component menu
		if (ImGui::Button("Add Component")) {
			ImGui::OpenPopup("add_component");
		}

		if (ImGui::BeginPopup("add_component")) {
			ImGui::Text("Components");

			ImGui::Separator();

			if (!hasRenderable) {
				if (ImGui::Selectable("Renderable Component")) {
					m_showAddRenderableWidget = true;
				}
			}

			if (!hasBC2D) {
				if (ImGui::Selectable("BoxCollider2D Component")) {
					m_clickedEntity->AddComponent(new ecs::BoxCollider2D())->Start();
				}
			}

			if (!hasSC) {
				if (ImGui::Selectable("Sound Component")) {
					m_clickedEntity->AddComponent(new ecs::SoundComponent())->Start();
				}
			}

			if (!hasMove) {
				if (ImGui::Selectable("Four-way Move Component")) {
					m_clickedEntity->AddComponent(new ecs::FourWayMoveComponent())->Start();
				}
			}

			ImGui::EndPopup();

		}

		if (m_showAddRenderableWidget) {
			ImGui::BeginChild("Add Renderable", ImVec2(250,250), true);

			static int type = 0; 
			// 0 - rectangle
			// 1 - sprite
			// 2 - triangle?
			static ImVec2 size = ImVec2(0,0);
			static ImVec4 color = ImVec4(1,0,0,1);
			static char imagePath[128] = "";

			if (ImGui::Button("Type")) {
				ImGui::OpenPopup("type");
			}
			if (ImGui::BeginPopup("type")) {
				if(ImGui::Selectable("Rectangle")) type = 0;
				if (ImGui::Selectable("Sprite")) type = 1;

				ImGui::EndPopup();
			}
			ImGui::SameLine(50);
			if (type == 0)
				ImGui::Text("Type: Rectangle");
			if (type == 1)
				ImGui::Text("Type: Sprite");
			if (type == 2)
				ImGui::Text("Type: Triangle");

			ImGui::Separator();

			if (type == 0) { // Rectangle
				ImGui::InputFloat2("Size", (float*)&size, 1);
				ImGui::ColorEdit4("Color", (float*)&color, true);
			}
			else if (type == 1) { // Sprite
				ImGui::InputText("Image Path", imagePath, 128);
			}

			ImGui::Separator();

			if (ImGui::Button("Add")) {
				if (type == 0)
					m_clickedEntity->AddComponent(new ecs::RectangleComponent(math::Vector2(size.x, size.y), math::Color(color.x, color.y, color.z, color.w) * 255))->Start();
				else if (type == 1)
					m_clickedEntity->AddComponent(new ecs::SpriteComponent(imagePath))->Start();
				m_showAddRenderableWidget = false;
			}

			ImGui::SameLine(60);

			if (ImGui::Button("Cancel")) {
				m_showAddRenderableWidget = false;
			}

			ImGui::EndChild();
		}

		ImGui::End();
	}
}

}}