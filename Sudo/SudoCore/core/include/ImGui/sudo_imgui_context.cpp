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

#include<string>
#include<vector>

#include"../ecs/entity.h"

namespace sudo { namespace debug { 

SudoImGui::SudoImGui() 
{
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
	ImGui::Columns(3, "columns3", false);
	for (int i = 0; i < entityList.size(); i++) 
	{
		if (!entityList[i]->DestroyMe()) {
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

	ImGui::End();
}


void SudoImGui::ShowSystemsWindow()
{
	if (m_showSystemsWindow) 
	{
		ImGui::SetNextWindowSize(ImVec2(300, 200));

		ImGui::Begin("Sudo Systems", &m_showSystemsWindow, 
			ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_::ImGuiWindowFlags_NoMove
		);
		/*
		../systems/settings_system.h <- This one shouldn't be fucked with!
		../systems/input_system.h
		../systems/particle_system.h
		../systems/sound_system.h
		../systems/text_system.h
		../systems/world_system.h
		../systems/batch_render_system.h
		*/
		// List all the asshole-systems

		if (m_renderSystem->IsActive()) ImGui::TextColored(ImVec4(0, 255, 0, 255), "Render System");
		else						    ImGui::TextColored(ImVec4(255, 0, 0, 255), "Render System");
		ImGui::SameLine(150);
		if (ImGui::Button("Toggle##1")) {
			m_renderSystem->Toggle();
		}

		if(m_inputSystem->IsActive()) ImGui::TextColored(ImVec4(0,255,0,255),    "Input System");
		else						  ImGui::TextColored(ImVec4(255, 0, 0, 255), "Input System");
		ImGui::SameLine(150);
		if (ImGui::Button("Toggle##2")) {
			m_inputSystem->Toggle();
		}

		if (m_particleSystem->IsActive()) ImGui::TextColored(ImVec4(0, 255, 0, 255), "Particle System");
		else						      ImGui::TextColored(ImVec4(255, 0, 0, 255), "Particle System");
		ImGui::SameLine(150);
		if (ImGui::Button("Toggle##3")) {
			m_particleSystem->Toggle();
		}

		if (m_soundSystem->IsActive())  ImGui::TextColored(ImVec4(0, 255, 0, 255), "Sound System");
		else						    ImGui::TextColored(ImVec4(255, 0, 0, 255), "Sound System");
		ImGui::SameLine(150);
		if (ImGui::Button("Toggle##4")) {
			m_soundSystem->Toggle();
		}

		if (m_textSystem->IsActive())  ImGui::TextColored(ImVec4(0, 255, 0, 255), "Text System");
		else						   ImGui::TextColored(ImVec4(255, 0, 0, 255), "Text System");
		ImGui::SameLine(150);
		if (ImGui::Button("Toggle##5")) {
			m_textSystem->Toggle();
		}

		if (m_worldSystem->IsActive()) ImGui::TextColored(ImVec4(0, 255, 0, 255), "World System");
		else						   ImGui::TextColored(ImVec4(255, 0, 0, 255), "World System");
		ImGui::SameLine(150);
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
		ImGui::Begin("Entity Inspector", &m_showEntityInspector);

		std::string id = "ID: " + std::string(m_clickedEntity->GetID());
		ImGui::Text(id.c_str());

		if (m_clickedEntity->DestroyMe()) {
			ImGui::Text("State: Destroyed");
		}
		else if (m_clickedEntity->IsActive()) {
			ImGui::Text("State: Active");
		}
		else {
			ImGui::Text("State: Disabled");
		}

		if (ImGui::Button("Toggle")) {
			m_clickedEntity->Toggle();
		}
		if (ImGui::Button("Destroy")) {
			m_clickedEntity->Destroy();
			m_showEntityInspector = false;
		}
		
		ImGui::End();
	}
}

}}