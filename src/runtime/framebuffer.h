#pragma once
#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H
#include <unordered_map>
#include <memory>
#include <GL/glew.h>
#include "texture.h"
namespace Zxen {
	class FrameBuffer {
	public:
		FrameBuffer() = default;
		~FrameBuffer() = default;
		void Setup()
		{

		}
		void AddAttachment(unsigned int type, TexturePtr texture)
		{
			attachments[type] = texture;
		}
		void Submit()
		{
			glGenFramebuffers(1, &FBID);
			glBindFramebuffer(GL_FRAMEBUFFER, FBID);
			for (auto iter : attachments) {
				glFramebufferTexture2D(GL_FRAMEBUFFER, iter.first, GL_TEXTURE_2D, iter.second->GetTextureID(), 0);
			}
		}
		GLuint GetFBID()
		{
			return FBID;
		}
	protected:
		GLuint FBID;
		std::unordered_map<unsigned int, TexturePtr> attachments;
	};
	using FrameBufferPtr = std::shared_ptr<FrameBuffer>;
}
#endif // !FRAME_BUFFER_H
