#include "../include/systems/settings_system.h"

#include<GLFW\glfw3.h>

namespace sudo { namespace sudo_system {

	SettingsSystem* SettingsSystem::_instance = nullptr;

	SettingsSystem * sudo::sudo_system::SettingsSystem::Instance()
	{
		if (_instance == nullptr)
			_instance = new SettingsSystem();
		return _instance;
	}

	const math::Vector2& SettingsSystem::GetWindowSize()
	{
		return m_windowSize;
	}

	const math::Color& SettingsSystem::GetBackgroundColor()
	{
		return m_backgroundColor;
	}

	const bool SettingsSystem::DoAutoRender()
	{
		return m_autoRender;
	}

	const bool SettingsSystem::ShowDebugOverlay()
	{
		return m_showDebugOverlay;
	}

	unsigned int SettingsSystem::GetCurrentFPS() const
	{
		return m_currentFps;
	}

	double SettingsSystem::GetCurrentMS() const
	{
		return m_currentMS;
	}

	SudoRenderMode SettingsSystem::GetRenderMode() const
	{
		return m_renderMode;
	}

	unsigned int SettingsSystem::GetFPS() const
	{
		return m_fps;
	}

	double SettingsSystem::GetMS() const
	{
		return m_msPerFrame;
	}

	void SettingsSystem::SetWindowSize(math::Vector2& a_newWindowSize) 
	{
		m_windowSize = a_newWindowSize;
	}

	void SettingsSystem::SetBackgroundColor(const math::Color& a_newBackgroundColor)
	{
		m_backgroundColor = a_newBackgroundColor;
	}

	void SettingsSystem::SetBackgroundColor(const double a_newBackgroundColor)
	{
		m_backgroundColor = math::Color(a_newBackgroundColor, a_newBackgroundColor,a_newBackgroundColor, 255);
	}

	void SettingsSystem::SetWindowCaption(const char* a_newCaption)
	{
		glfwSetWindowTitle(glfwGetCurrentContext(), a_newCaption);
	}

	void SettingsSystem::SetFPS(const unsigned int a_newFPS) 
	{
		m_fps = a_newFPS;
		this->NewFpsValue();
	}

	void SettingsSystem::SetCurrentFPS(const unsigned int a_currentNewFps)
	{
		m_currentFps = a_currentNewFps;
	}

	void SettingsSystem::SetCurrentMS(const double a_newMS)
	{
		m_currentMS = a_newMS;
	}

	void SettingsSystem::SetRenderMode(SudoRenderMode a_mode)
	{
		m_renderMode = a_mode;
	}

	void SettingsSystem::ShowDebugOverlay(bool a_show)
	{
#ifdef _DEBUG
		m_showDebugOverlay = a_show;
#else
		m_showDebugOverlay = false;
#endif
	}

	void SettingsSystem::NewFpsValue()
	{
		if (m_fps > 0)
			m_msPerFrame = 1000 / m_fps;
		else
			m_msPerFrame = 0;
	}

	void SettingsSystem::SetAutoRender(bool a_value) 
	{
		m_autoRender = a_value;
	}

}}
