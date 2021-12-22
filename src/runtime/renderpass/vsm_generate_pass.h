#pragma once
#ifndef VSM_GENERATE_PASS_H
#define VSM_GENERATE_PASS_H
#include "renderpass.h"
#include "GL/glew.h"
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>
#include "program.h"
#include "graphicNode.h"
#include "framebuffer.h"
#include "texture.h"
#include "material.h"
#include "depthpass.h"
namespace Zxen {
	class VsmGeneratePass : public DepthPass {
	public:
		VsmGeneratePass(ZXEngine* eng, GLint shadowWidth, GLint shadowHeight) : DepthPass(eng, shadowWidth, shadowHeight)
		{
		}
		virtual ~VsmGeneratePass() = default;
		virtual bool GenResources() override;
		virtual void Render();
	private:

	};
}

#endif // !VSM_GENERATE_PASS_H
