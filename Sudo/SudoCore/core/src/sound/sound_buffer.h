#pragma once

#include<al.h>
#include<alc.h>

namespace sudo { namespace sound { 

	class SoundBuffer {
	private:
		ALuint buffer;

	public:
		// Constructor
		SoundBuffer();
		
		// Destructor 
		~SoundBuffer();

		// Sets the sound buffers data 
		void setData(int a_format, char* a_data, int a_size, int a_sampleRate);

		// Returns sound buffer
		ALuint getBufferId() const { return buffer; }
	};

} } 