#pragma once

#include"component.h"
#include<map>

namespace sudo {
	namespace sound {
		class SoundBuffer;
		class SoundSource;
	} 
	namespace graphics {
		class Renderable2D;
	}
}

namespace sudo { namespace ecs { 

	struct SoundStruct {
		sound::SoundBuffer *soundBuffer;
		sound::SoundSource *soundSource;
	};

	class SoundComponent : public Component {
	private:
		std::map<const char*, SoundStruct*> m_soundList;

	public:
		// Default constructor, adds sound with a_soundName to m_soundList
		SoundComponent(const char* a_soundName, const char* a_soundPath);
		SoundComponent();

		// Adds sound with a_soundName to m_soundList
		void AddSound(const char* a_soundName, const char* a_soundPath);

		// Returns raw pointer to the audio source 
		sound::SoundSource *GetSoundSource(const char* a_name);

		// Returns a copy of the sound map
		std::map<const char*, SoundStruct*> GetSoundList();

		/* Component base methods */
		void Update(float deltaTime) override;
		void Start() override;
	};

} } 