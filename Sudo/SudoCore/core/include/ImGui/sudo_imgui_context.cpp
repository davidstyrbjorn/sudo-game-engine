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

#include"../graphics/renderable2d.h"
#include"../graphics/texture.h"
#include"../math/color.h"
#include"../math/vector2.h"

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
		if (ImGui::CollapsingHeader("Renderable"))
		{
			graphics::Renderable2D* renderable = m_clickedEntity->GetRenderableComponent();
			bool hasRenderbale = renderable == nullptr ? false : true;
			if (hasRenderbale) {
				ImGui::Text("Renderable Component: true");

				ImGui::Separator();

				// Size
				ImGui::BulletText("Size");
				float _x = renderable->GetSize().x;
				float _y = renderable->GetSize().y;
				ImGui::SliderFloat("Width", &_x, 0, m_settingsSystem->GetWindowSize().x, "%0.0f");
				ImGui::SliderFloat("Height", &_y, 0, m_settingsSystem->GetWindowSize().y, "%0.0f");
				renderable->SetSize(math::Vector2(_x, _y));

				ImGui::Separator();

				// Color
				ImGui::BulletText("Color");
				ImVec4 color = ImColor(renderable->GetColor().r / 255, renderable->GetColor().g / 255, renderable->GetColor().b / 255, renderable->GetColor().a / 255);
				ImGui::ColorEdit4("Renderable Color", (float*)&color);
				renderable->SetColor(math::Color(color.x * 255, color.y * 255, color.z * 255, color.w * 255));

				ImGui::Separator();

				// Texture
				auto _txtre = renderable->GetTexture();
				if (_txtre != nullptr) {
					//ImGui::Text("Texture: true");
					ImGui::BulletText("Texture");

					std::string _imagePath = std::string(_txtre->getImagePath());
					int _index = _imagePath.find_last_of("\\")+1;
					std::string _imageName = "Name: ";
					for (int i = _index; i < _imagePath.length(); ++i) {
						_imageName.append(1, _imagePath.at(i));
					}
					ImGui::Text(_imageName.c_str());

					std::string imagePath = "Location: " + std::string(_txtre->getImagePath());
					ImGui::Text(imagePath.c_str());
				}
				else {
					ImGui::Text("Texture: nullptr");
				}
			}
			else {
				ImGui::Text("Renderable Component: nullptr");
			}
		}

		// BoxCollider2D component
		if (ImGui::CollapsingHeader("BoxCollider2D")) {
			// Check if entity has boxcollider2d component
			ecs::BoxCollider2D* _bc2d = m_clickedEntity->GetComponent<ecs::BoxCollider2D>();
			bool hasBC2D = (_bc2d == nullptr) ? false : true;
			if (hasBC2D) {
				ImGui::Text("BoxCollider2D Component: true");

				ImGui::Text("Origin: (100, 25)");
			}
			else {
				ImGui::Text("BoxCollider2D Component: nullptr");
			}
		}

		// Four-way move component
		if (ImGui::CollapsingHeader("Four-way Move")) {
			// Check if entity has fourway_move component
			ecs::FourWayMoveComponent* _fwm = m_clickedEntity->GetComponent<ecs::FourWayMoveComponent>();
			bool hasMove = (_fwm == nullptr) ? false : true;
			if (hasMove) {
				ImGui::Text("Four-way Move Component: true");

				ImGui::Separator(); ImGui::Spacing();

				// Velocity
				ImVec2 fwm_velocity = ImVec2(_fwm->GetVelocity().x, _fwm->GetVelocity().y);

				//ImGui::SliderFloat2("Velocity", (float*)&fwm_velocity, 0, 10);
				ImGui::InputFloat2("Velocity(x,y)", (float*)&fwm_velocity);

				_fwm->SetVelocity(math::Vector2(fwm_velocity.x, fwm_velocity.y));

				ImGui::Separator();

				// Keys
				ImGui::Text("Move Keys (right click to change!)");
				int up_code 

				// Moving up key 
				ImGui::Text("Up");
				ImGui::SameLine(0,-5.0f);


				// Moving down key
				ImGui::Text("Down");

				ImGui::SameLine();

				// Moving right key
				ImGui::Text("Right");

				ImGui::SameLine();

				// Moving left key
				ImGui::Text("Left");

				if(ImGui::Button("Set##fwm")){
					_fwm->SetKeys(up_buf, down, right, left);
			}
			else {
				ImGui::Text("Four-way Move Component: nullptr");
			}
		}
		
		ImGui::End();
	}
}

}}