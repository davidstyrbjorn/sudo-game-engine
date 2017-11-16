#pragma once

#include"../../../definitions.h"

namespace sudo { namespace graphics {

	class IndexBuffer {
	public:
		IndexBuffer();
		IndexBuffer(unsigned int a_indices[], uint a_size);

		void bind() const;
		void unbind() const;

	private:
		unsigned int m_buffer;
	};
	
} }