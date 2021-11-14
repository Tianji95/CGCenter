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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return true;
}

void DepthPass::SetLightSpaceMatrixUniform(std::shared_ptr<ShaderBase> program, int shadowType, int shadowLightSize) const
{
	glUniformMatrix4fv(glGetUniformLocation(program->GetID(), "LightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
	GLuint shadowLightPosID = glGetUniformLocation(program->GetID(), "shadow_light_pos");
	glUniform3fv(shadowLightPosID, 1, &pos[0]);

	GLuint shadowTypeID = glGetUniformLocation(program->GetID(), "shadow_type");
	glUniform1i(shadowTypeID, shadowType);

	GLuint shadowLightSizeID = glGetUniformLocation(program->GetID(), "shadow_light_size");
	glUniform1i(shadowLightSizeID, shadowLightSize);
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
	SetLightSpaceMatrixUniform(program, 2, 2);
}
