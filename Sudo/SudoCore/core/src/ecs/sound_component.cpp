#include "sound_component.h"

#include"../sound/sound_include.h"

#include<al.h>
#include<alc.h>

#include"entity.h"

#include"../debug.h"

#include"../math/vector2.h"

namespace sudo { namespace ecs {

SoundComponent::SoundComponent(const char * a_soundPath)
{
	m_soundPath = a_soundPath;

	// Loading .wav file
	int format, size, sampleRate, channel, bps;
	char* data = loadWAV(m_soundPath, channel, sampleRate, bps, size, format);

	// Creating the sound buffer
	soundBuffer = new sound::SoundBuffer();
	soundBuffer->setData(format, data, size, sampleRate);

	// Creating the sound source
	soundSource = new sound::SoundSource(soundBuffer->getBufferId());
}

void SoundComponent::Start() 
{

}

void SoundComponent::Update() 
{
	// Update the source's position to be identical to the m_entityHolder-transform->position! 
	// Important for the dynamic sound OpenAL provides
	math::Vector2 ratioPosition = math::Vector2(m_entityHolder->transform->position.x/800, m_entityHolder->transform->position.y/600);

	if (soundSource->getPosition() != m_entityHolder->transform->position) {
		soundSource->setPosition(m_entityHolder->transform->position);
	}
}

sound::SoundSource *SoundComponent::GetSoundSource() 
{
	return soundSource;
}

} } 