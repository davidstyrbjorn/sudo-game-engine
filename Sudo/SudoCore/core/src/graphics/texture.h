#pragma once

#include"../../gl_include.h"
typedef unsigned int uint;

namespace sudo { namespace graphics {

	class Texture {
	public:
		/* Default constructor */
		Texture();

		/* 2nd Constructor, takes in a path to the image (can be either .jpg or .png) */
		/* Using SOIL2 to load image data */
		Texture(char* a_imagePath);

		/* Destructor */
		~Texture();

		/* Binds the texture buffer */
		void bind() const;

		/* Size getters */
		__forceinline uint getWidth() { return m_width; }
		__forceinline uint getHeight() { return m_height; }

	public:
		/* Texture data */
		GLuint m_texId;
		int m_width, m_height;
	};
		
} }