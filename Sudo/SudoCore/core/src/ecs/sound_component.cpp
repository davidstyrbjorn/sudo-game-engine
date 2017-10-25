#include "sound_component.h"

#include"../sound/sound_include.h"

#include<al.h>
#include<alc.h>

#include"entity.h"

#include"../debug.h"

#include"../math/vector2.h"
#include"../graphics/renderable2d.h"

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
	/* Get the Renderable2D component attatched to m_entityHolder */
	for (int i = 0; i < m_entityHolder->GetComponentList().size(); i++) {
		if (dynamic_cast<graphics::Renderable2D*>(m_entityHolder->GetComponentList()[i]) != nullptr) {
			m_entityRenderableComponent = dynamic_cast<graphics::Renderable2D*>(m_entityHolder->GetComponentList()[i]);
		}
	}
}

void SoundComponent::Update() 
{
	// Update the source's position to be identical to the m_entityHolder-transform->position! 
	// Important for the dynamic sound OpenAL provides
	math::Vector2 ratioPosition = math::Vector2(m_entityHolder->transform->position.x/800, m_entityHolder->transform->position.y/600);
	if (soundSource->getPosition() != m_entityHolder->transform->position) {
		soundSource->setPosition(m_entityHolder->transform->position);
	}

	std::cout << m_entityRenderableComponent->GetSize() << std::endl;
}

sound::SoundSource *SoundComponent::GetSoundSource() 
{
	return soundSource;
}

} } 