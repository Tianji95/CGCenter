#include "depthpass.h"
#include "glm/gtc/type_ptr.hpp"
#include "program.h"

bool DepthPass::GenResources()
{
	glGenFramebuffers(1, &depthMapFBO);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return true;
}

void DepthPass::SetLightSpaceMatrixUniform(std::shared_ptr<ShaderBase> program) const
{
	glUniformMatrix4fv(glGetUniformLocation(program->GetID(), "LightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
}

void DepthPass::UseShadowMap(std::shared_ptr<ShaderBase> program)
{
	auto textureID = glGetUniformLocation(program->GetID(), "shadow_map");
	glActiveTexture(GL_TEXTURE0+18);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(textureID, 18);
}

void DepthPass::Render(std::shared_ptr<ShaderBase> program) const
{
	glViewport(0, 0, width, height);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	SetLightSpaceMatrixUniform(program);
}
