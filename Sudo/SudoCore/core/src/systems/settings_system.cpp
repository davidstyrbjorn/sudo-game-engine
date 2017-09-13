#include "settings_system.h"

namespace sudo { namespace system {

	SettingsSystem* SettingsSystem::_instance = nullptr;

	SettingsSystem * sudo::system::SettingsSystem::Instance()
	{
		if (_instance == nullptr)
			_instance = new SettingsSystem();
		return _instance;
	}

	const math::Vector2& SettingsSystem::GetWindowSize()
	{
		return m_windowSize;
	}

	const math::Vector4& SettingsSystem::GetBackgroundColor()
	{
		return m_backgroundColor;
	}

	unsigned int SettingsSystem::GetFPS() const
	{
		return m_fps;
	}

	double SettingsSystem::GetMS() const
	{
		return m_msPerFrame;
	}

	void SettingsSystem::SetWindowSize(const math::Vector2& a_newWindowSize) 
	{
		m_windowSize = a_newWindowSize;
	}

	void SettingsSystem::SetBackgroundColor(const math::Vector4& a_newBackgroundColor)
	{
		m_backgroundColor = a_newBackgroundColor;
	}

	void SettingsSystem::SetFPS(const unsigned int a_newFPS) 
	{
		m_fps = a_newFPS;
		this->NewFpsValue();
	}

}}
