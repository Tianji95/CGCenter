#pragma once
#ifndef VSM_GENERATE_PASS_H
#define VSM_GENERATE_PASS_H
#include "renderpass.h"
#include "GL/glew.h"
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>
#include "shaderBase.h"

class VsmGeneratePass : public RenderPass {
public:
	VsmGeneratePass(glm::vec3 eye, glm::vec3 look, glm::vec3 up)
	{
		GLfloat near_plane = 0.1f, far_plane = 10000.0f;
		glm::mat4 lightProjection = glm::ortho(-2000.0f, 2000.0f, -2000.0f, 2000.0f, near_plane, far_plane);
		glm::mat4 lightView = glm::lookAt(eye, look, up);
		lightSpaceMatrix = lightProjection * lightView;
		pos = eye;
		lookat = look;
	}
	virtual ~VsmGeneratePass() = default;
	virtual bool GenResources() override;
	void SetLightSpaceMatrixUniform(std::shared_ptr<ShaderBase> program, int shadowType, int shadowLightSize) const;
	void UseShadowMap(std::shared_ptr<ShaderBase> program);
	virtual void Render(std::shared_ptr<ShaderBase> program) const;
private:
	GLuint FBO;
	GLint width = 1024;
	GLint height = 1024;
	GLuint texture = 0;
	glm::vec3 pos;
	glm::vec3 lookat;
	glm::mat4 lightSpaceMatrix;
};


#endif // !VSM_GENERATE_PASS_H
