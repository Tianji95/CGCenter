#pragma once
#ifndef SHADOW_PASS_H
#define SHADOW_PASS_H
#include "renderpass.h"
#include <GL/glew.h>
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>
#include "program.h"
#include "graphicNode.h"
#include "framebuffer.h"
#include "texture.h"
#include "material.h"
namespace Zxen {
	class ZXEngine;
	class DepthPass : public RenderPass {
	public:
		DepthPass(ZXEngine* eng, GLint shadowWidth, GLint shadowHeight) : RenderPass(eng), width(shadowWidth), height(shadowHeight)
		{
		}
		virtual ~DepthPass() = default;
		virtual bool GenResources() override;
		virtual void Setup(glm::vec3 eye, glm::vec3 look, glm::vec3 up, glm::vec4 ortho, GLfloat nearplane, GLfloat farplane)
		{
			glm::mat4 lightProjection = glm::ortho(ortho.x, ortho.y, ortho.z, ortho.w, nearplane, farplane);
			glm::mat4 lightView = glm::lookAt(eye, look, up);
			lightSpaceMatrix = lightProjection * lightView;
			pos = eye;
			lookat = look;
		}
		virtual void Render();
		virtual void InsertGraphNode(RenderGraph* renderGraph) override;
		virtual void UpdateRenderData() override;
		virtual Texture2DPtr GetDepthTexture();
		void SetLightSpaceMatrixUniform(std::shared_ptr<Program> program) const;
		virtual void SetShadowType(unsigned int type);
		virtual void SetShadowLightSize(unsigned int lightsize);

	protected:
		unsigned int shadowType;
		unsigned int shadowLightSize;
		MaterialPtr material;
		ProgramPtr prog;
		FrameBufferPtr fb;
		Texture2DPtr depthTexture;
		GLint width = 1024;
		GLint height = 1024;
		GLuint texture = 0;
		glm::vec3 pos;
		glm::vec3 lookat;
		glm::mat4 lightSpaceMatrix;
		std::unique_ptr<GraphicNode> node;
	};
}
#endif // !SHADOW_PASS_H

