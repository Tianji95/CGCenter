#pragma once
#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H
#include <GL/glew.h>
namespace Zxen {
	struct IndexBuffer {
		unsigned int GetDataTypeSize()
		{
			switch (type) {
			case GL_UNSIGNED_INT:
			{
				return 4;
			}
			case GL_UNSIGNED_SHORT: {
				return 2;
			}
			case GL_UNSIGNED_BYTE: {
				return 1;
			}
			}
		}
		void* buffer;
		GLenum type;
		unsigned int indexCount;
	};
}
#endif // !INDEX_BUFFER_H
