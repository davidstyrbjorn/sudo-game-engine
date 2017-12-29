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

#include"../graphics/renderable2d.h"
#include"../ecs/transform_component.h"
#include"../math/color.h"

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
	ImGui::Begin("Sudo Entities", false, ImVec2(250, 150), 0.7f, 
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

	std::string temp = "Count: " + std::to_string(entityList.size());
	ImGui::Text(temp.c_str());

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

		float position[2] = { m_clickedEntity->transform->position.x, m_clickedEntity->transform->position.y };

		std::string id = "ID: " + std::string(m_clickedEntity->GetID());
		ImGui::Text(id.c_str());
		ImGui::Text("Position:");
		ImGui::SliderFloat2("test", position, 0, m_settingsSystem->GetWindowSize().x, "%0.0f");
		m_clickedEntity->transform->position = math::Vector3(position[0], position[1], m_clickedEntity->transform->position.z);
		ImGui::Text("Rotation:");
		ImGui::SliderFloat(" :z", &m_clickedEntity->transform->angle, -360, 360, "%0.0f");

		ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();

		// Active state text
		if (m_clickedEntity->IsActive()) {
			ImGui::Text("State: Active");
		}
		else {
			ImGui::Text("State: Disabled");
		}

		// State Modification buttons
		if (ImGui::Button("Toggle")) {
			m_clickedEntity->Toggle();
		}
		if (ImGui::Button("Destroy")) {
			m_clickedEntity->Destroy();
			m_showEntityInspector = false;
		}

		ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
		
		graphics::Renderable2D* renderable = m_clickedEntity->GetRenderableComponent();
		bool hasRenderbale = renderable == nullptr ? false : true;
		if (hasRenderbale) {
			ImGui::Text("Renderable Component: true");
			
			float _x = renderable->GetSize().x;
			float _y = renderable->GetSize().y;
			ImGui::SliderFloat("Width", &_x, 0, m_settingsSystem->GetWindowSize().x, "%0.0f");
			ImGui::SliderFloat("Height", &_y, 0, m_settingsSystem->GetWindowSize().y, "%0.0f");
			renderable->SetSize(math::Vector2(_x, _y));
			
			ImVec4 color = ImColor(renderable->GetColor().r/255, renderable->GetColor().g/255, renderable->GetColor().b/255, renderable->GetColor().a/255);
			ImGui::ColorEdit4("Renderable Color", (float*)&color);
			renderable->SetColor(math::Color(color.x*255, color.y*255, color.z*255, color.w*255));
		}
		else {
			ImGui::Text("Renderable Component: nullptr");
		}
		
		ImGui::End();
	}
}

}}