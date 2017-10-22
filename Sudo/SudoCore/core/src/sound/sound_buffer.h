#pragma once

#include<al.h>
#include<alc.h>

namespace sudo { namespace sound { 

	class SoundBuffer {
	private:
		ALuint buffer;

	public:
		/* Default constructor */
		SoundBuffer();
		
		/* Destructor */
		~SoundBuffer();

		/* Sets the sound buffers data */
		void setData(int a_format, char* a_data, int a_size, int a_sampleRate);

		/* Getter for the sound buffers id */
		ALuint getBufferId() { return buffer; }
	};

} } 