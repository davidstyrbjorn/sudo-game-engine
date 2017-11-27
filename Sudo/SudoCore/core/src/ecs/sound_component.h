#pragma once

#include"component.h"

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

	class SoundComponent : public Component {
	private:
		sound::SoundBuffer *soundBuffer;
		sound::SoundSource *soundSource;

		graphics::Renderable2D *m_entityRenderableComponent;

		const char* m_soundPath;

	public:
		/* Default constructor takes in path to .wav file for initalizing */
		SoundComponent(const char* a_soundPath);

		/* Returns raw pointer to the audio source */
		sound::SoundSource *GetSoundSource();

		/* Component base methods */
		void Update(float deltaTime) override;
		void Start() override;
	};

} } 