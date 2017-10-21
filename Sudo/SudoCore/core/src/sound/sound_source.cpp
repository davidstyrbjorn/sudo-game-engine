#include "sound_source.h"

#include"../debug.h"
#include"../math/vector3.h"

#include<fstream>

namespace sudo { namespace sound { 

	bool isBigEndian()
	{
		int a = 1;
		return !((char*)&a)[0];
	}

	int convertToInt(char* buffer, int len)
	{
		int a = 0;
		if (!isBigEndian())
			for (int i = 0; i<len; i++)
				((char*)&a)[i] = buffer[i];
		else
			for (int i = 0; i<len; i++)
				((char*)&a)[3 - i] = buffer[i];
		return a;
	}

	char* loadWAV(const char* fn, int& chan, int& samplerate, int& bps, int& size, int& format)
	{
		char buffer[4];
		std::ifstream in(fn, std::ios::binary);

		// Master riff chunk at the first 4 bytes should be "RIFF" if it's a .wav file
		in.read(buffer, 4);
		if (strncmp(buffer, "RIFF", 4) != 0)
		{
			std::cout << "this is not a valid WAVE file" << std::endl;
			return NULL;
		}

		// Still master riff chunk
		in.read(buffer, 4);		// 4+n
		in.read(buffer, 4);     // WAVE

		in.read(buffer, 4);     // fmt
		in.read(buffer, 4);     // Chunk size: 16, 18 or 40
		in.read(buffer, 2);     // Format code: 1
		in.read(buffer, 2);
		chan = convertToInt(buffer, 2);

		in.read(buffer, 4);		// Sampling rate
		samplerate = convertToInt(buffer, 4);

		in.read(buffer, 4);		// Data Rate (byte/sec)
		in.read(buffer, 2);		// Data block size (bytes)
		in.read(buffer, 2);		// Bits per sample
		bps = convertToInt(buffer, 2);

		in.read(buffer, 4);     // Subchunk2ID -> "data"
		in.read(buffer, 4);		// Subchunk2Size -> NumSamples * NumChannels * BitsPerSample/8
		size = convertToInt(buffer, 4);

		char* data = new char[size];
		in.read(data, size);	// Reading the actual waveform data 

								// Setting the format
		if (chan == 1) {
			if (bps == 8)
				format = AL_FORMAT_MONO8;
			else
				format = AL_FORMAT_MONO16;
		}
		else {
			if (bps == 8)
				format = AL_FORMAT_STEREO8;
			else
				format = AL_FORMAT_STEREO16;
		}

		// Return the waveform data
		return data;
	}

SoundSource::SoundSource(ALuint a_buffer)
{
	alGenSources(1, &source);
	if (alGetError() != AL_NO_ERROR) {
		DEBUG::getInstance()->printMessage("Error creating source with id " + source, LogType::Error);
	}

	alSourcef(source, AL_GAIN, 1);
	alSourcef(source, AL_PITCH, 1);
	alSource3f(source, AL_POSITION, 0, 0, 15);

	int format, size, sampleRate, channel, bps;
	char* data = loadWAV("C:\\temp\\sound.wav", channel, sampleRate, bps, size, format);

	ALuint buffer;
	alGenBuffers(1, &buffer);
	alBufferData(buffer, format, data, size, sampleRate);

	alSourcei(source, AL_BUFFER, buffer);

	alSourcePlay(source);
}

void SoundSource::setPosition(const math::Vector3 & a_position)
{
	m_position = a_position;
	alSource3f(source, AL_POSITION, m_position.x, m_position.y, m_position.z);
}

void SoundSource::setVolume(const float a_gain)
{
	alSourcef(source, AL_GAIN, abs(a_gain));
}

void SoundSource::play()
{
	std::cout << "Play audio source" << std::endl;
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