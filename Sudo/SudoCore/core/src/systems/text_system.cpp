#include"text_system.h"

namespace sudo { namespace sudo_system { 

	TextSystem * TextSystem::_instance = nullptr;

	TextSystem* TextSystem::Instance() 
	{
		if (_instance == nullptr)
			_instance = new TextSystem();
		return _instance;
	}

	void TextSystem::Update() 
	{

	}

	void TextSystem::Start()
	{

	}

	void TextSystem::Enable()
	{

	}

	void TextSystem::Disable()
	{

	}

	void TextSystem::CleanUp()
	{

	}

} } 