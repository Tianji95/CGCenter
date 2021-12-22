#include "texture.h"
namespace Zxen {
	bool Texture::isSameName(std::string& rpath)
	{
		return std::strcmp(name.data(), rpath.c_str()) == 0;
	}

	unsigned int Texture::GetHandle()
	{
		return handle;
	}

	std::string& Texture::GetTextureTypeName()
	{
		return textureType;
	}

	unsigned int Texture::GetTextureID()
	{
		return textureID;
	}

	void Texture2D::Setup(std::string& type, unsigned int width, unsigned int height, unsigned int mipmapLevel, GLenum internalFormat, GLenum format, GLenum datatype, void* bufptr)
	{
		buffer = bufptr;
		this->textureType = type;
		this->width = width;
		this->height = height;
		this->mipmapLevel = mipmapLevel;
		this->format = format;
		this->internalFormal = format;
		this->dataType = datatype;
	}

	void Texture2D::Submit()
	{
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // read texture use 1 Byte alighment, avoid crash using 4 Byte alighment
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormal, width, height, 0, format, dataType, buffer);
		glGenerateMipmap(GL_TEXTURE_2D);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		if (hasBorder) {
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		}
	}

	void Texture2D::SetupBorderColor(GLfloat borderColor[4])
	{
		for (int i = 0; i < 4; i++) {
			this->borderColor[i] = borderColor[i];
		}
		hasBorder = true;
	}

	void Cubemap::Setup(std::string& type, int width[6], int height[6], int mipmapLevel, GLenum format[6], GLenum datatype, std::vector<void*>& bufptr)
	{
		this->textureType = type;
		cubebuffers = bufptr;
		for (int i = 0; i < 6; i++) {
			this->width[i] = width[i];
			this->height[i] = height[i];
			this->format[i] = format[i];
		}
		this->mipmapLevel = mipmapLevel;
		this->dataType = datatype;
	}

	void Cubemap::Submit()
	{
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		for (unsigned int i = 0; i < 6; i++) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format[i], width[i], height[i], 0, format[i], dataType, cubebuffers[i]);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}
}