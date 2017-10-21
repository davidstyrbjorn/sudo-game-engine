#pragma once

#include"component.h"

namespace sudo {
	namespace sound {
		class SoundBuffer;
		class SoundSource;
} }

namespace sudo { namespace ecs { 

	class SoundComponent : public Component {
	private:
		sound::SoundBuffer *soundBuffer;
		sound::SoundSource *soundSource;

	public:
		/* Default constructor takes in path to .wav file for initalizing */
		SoundComponent(const char* a_soundPath);

		/* Returns raw pointer to the audio source */
		sound::SoundSource *GetSoundSource();

		/* Component base methods */
		void Update() override;
		void Start() override { } 
	};

} } 