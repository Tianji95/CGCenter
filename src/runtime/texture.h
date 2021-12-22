#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H
#include <vector>
#include <string>
#include <memory>
#include <GL/glew.h>
namespace Zxen {
	class Texture {
	public:
		Texture(std::string& name, unsigned int handle, GLenum bindType) : handle(handle), textureID(0), textureType(""), name(name), mipmapLevel(0), dataType(GL_UNSIGNED_BYTE), bindType(bindType)
		{

		}
		virtual ~Texture() = default;
		virtual void Submit() = 0;

		bool isSameName(std::string& rpath);
		unsigned int GetHandle();
		std::string& GetTextureTypeName();
		unsigned int GetTextureID();
		GLenum bindType;

	protected:
		unsigned int handle;
		unsigned int textureID;
		std::string textureType;
		std::string name;
		unsigned int mipmapLevel;
		GLenum dataType;
	};
	using TexturePtr = std::shared_ptr<Texture>;

	class Texture2D : public Texture {
	public:
		Texture2D(std::string& name, unsigned int handle) : Texture(name, handle, GL_TEXTURE_2D),
			width(0), height(0), format(GL_RGBA), buffer(nullptr)
		{
		}
		virtual ~Texture2D() = default;
		virtual void Setup(std::string& type, unsigned int width, unsigned int height, unsigned int mipmapLevel, GLenum internalFormat, GLenum format, GLenum datatype, void* bufptr);
		virtual void Submit();
		virtual void SetupBorderColor(GLfloat borderColor[4]);
	protected:
		void* buffer;
		unsigned int width;
		unsigned int height;
		GLenum format;
		GLenum internalFormal;
		bool hasBorder = false;
		GLfloat borderColor[4];
	};
	using Texture2DPtr = std::shared_ptr<Texture2D>;

	class Cubemap : public Texture {
	public:
		Cubemap(std::string& name, unsigned int handle) : Texture(name, handle, GL_TEXTURE_CUBE_MAP)
		{
		}
		virtual ~Cubemap() = default;
		void Setup(std::string& type, int width[6], int height[6], int mipmapLevel, GLenum format[6], GLenum datatype, std::vector<void*>& bufptr);
		void Submit();
	private:
		std::vector<void*> cubebuffers;
		unsigned int width[6];
		unsigned int height[6];
		GLenum format[6];
	};
	using CubemapPtr = std::shared_ptr<Cubemap>;
}
#endif // !TEXTURE_H
