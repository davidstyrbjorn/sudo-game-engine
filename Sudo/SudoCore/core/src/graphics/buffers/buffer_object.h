#pragma once

typedef unsigned int uint;

#include"../../../gl_include.h"

namespace sudo { namespace graphics { 
	
	class BufferObject {
	private:
		uint m_id;
		uint m_componentCount, m_attributeIndex;
		GLenum m_bufferType;

	public:
		/* Constructor */
		BufferObject();

		template<typename T>
		void init(GLenum type, T data[], uint attributeIndex, uint componentCount)
		{
			m_attributeIndex = attributeIndex;
			m_componentCount = componentCount;
			m_bufferType = type;

			glGenBuffers(1, &m_id);
			glBindBuffer(type, m_id);
			glBufferData(type, sizeof(*data), data, GL_STATIC_DRAW);

			if (attributeIndex != -1) {
				glVertexAttribPointer(m_attributeIndex, m_componentCount, GL_FLOAT, GL_FALSE, m_componentCount * sizeof(T), nullptr);
				glEnableVertexAttribArray(m_attributeIndex);
			}
		}

		/* Destructor */
		~BufferObject();

		/* Binds */
		void bind() const;

		/* Unbinds */
		void unbind() const;
	};

} } 