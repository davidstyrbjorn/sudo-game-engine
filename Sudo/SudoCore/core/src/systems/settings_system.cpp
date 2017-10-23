#include "settings_system.h"
#include"../../gl_include.h"
#include"../../sudo.h"

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

		// Audio Listener should be in the middle of the screen
		/*
		This throws unresolved external error, why the fuck does it do that!?
		SoundSystem *temp = SoundSystem::Instance();
		temp->SetListenerPosition(math::Vector3(a_newWindowSize.x / 2, a_newWindowSize.y / 2, 0));
		*/

		// This is not what I want to do 
		alListener3f(AL_POSITION, a_newWindowSize.x/2, a_newWindowSize.y/2, -1);
	}

	void SettingsSystem::SetBackgroundColor(const math::Vector4& a_newBackgroundColor)
	{
		m_backgroundColor = a_newBackgroundColor;
	}

	void SettingsSystem::SetBackgroundColor(const double a_newBackgroundColor)
	{
		m_backgroundColor = math::Vector4(a_newBackgroundColor, a_newBackgroundColor,a_newBackgroundColor,1);
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

}}
