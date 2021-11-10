#pragma once
#ifndef SHADOW_PASS_H
#define SHADOW_PASS_H
#include "renderpass.h"
#include <GL/glew.h>
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>
#include "shaderBase.h"
class DepthPass : public RenderPass{
public:
	DepthPass(glm::vec3 eye, glm::vec3 lootat, glm::vec3 up)
	{
		GLfloat near_plane = 0.1f, far_plane = 10000.0f;
		glm::mat4 lightProjection = glm::ortho(-1000.0f, 1000.0f, -1000.0f, 1000.0f, near_plane, far_plane);
		glm::mat4 lightView = glm::lookAt(eye, lootat, up);
		lightSpaceMatrix = lightProjection * lightView;
	}
	virtual ~DepthPass() = default;
	virtual bool GenResources() override;
	virtual void Render(std::shared_ptr<ShaderBase> program) const;
protected:
private:
	GLuint depthMapFBO;
	GLint width = 1024;
	GLint height = 1024;
	GLuint texture = 0;
	glm::mat4 lightSpaceMatrix;
};

#endif // !SHADOW_PASS_H

