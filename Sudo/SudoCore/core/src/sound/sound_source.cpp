#include "sound_source.h"

#include"../debug.h"
#include"../math/vector3.h"

#include<fstream>

namespace sudo { namespace sound { 

SoundSource::SoundSource(ALuint a_buffer)
{
	alGenSources(1, &source);
	if (alGetError() != AL_NO_ERROR) {
		DEBUG::getInstance()->printMessage("Error creating source with id " + source, LogType::Error);
	}

	// Attatch the sound buffer to this source
	alSourcei(source, AL_BUFFER, a_buffer);
}

SoundSource::~SoundSource()
{
	alDeleteBuffers(1, &source);
}

void SoundSource::setPosition(const math::Vector3 & a_position)
{
	m_position = a_position;
	alSource3f(source, AL_POSITION, m_position.x, m_position.y, m_position.z);
}

void SoundSource::setVolume(const float a_gain)
{
	alSourcef(source, AL_GAIN, a_gain);
}

void SoundSource::setLooping(unsigned char a_loop) 
{
	alSourcei(source, AL_LOOPING, true);
}

void SoundSource::setPitch(const float a_pitch) 
{
	alSourcef(source, AL_PITCH, a_pitch);
}

void SoundSource::play()
{
	ALint state;
	alGetSourcei(source, AL_SOURCE_STATE, &state);
	if(state != AL_PLAYING)
		alSourcePlay(source);
}

void SoundSource::pause() 
{
	alSourcePause(source);
}

void SoundSource::stop()
{
	alSourceStop(source);
}

void SoundSource::restart() 
{
	alSourceRewind(source);
	alSourcePlay(source);
}

} } 