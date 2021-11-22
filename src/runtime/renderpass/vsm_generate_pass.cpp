#include "vsm_generate_pass.h"
#include "glm/gtc/type_ptr.hpp"

bool VsmGeneratePass::GenResources()
{
	glGenFramebuffers(1, &FBO);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RG32F, width, height, 0, GL_RG, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTextureParameteri(texture, GL_TEXTURE_BASE_LEVEL, 0);
	glTextureParameteri(texture, GL_TEXTURE_MAX_LEVEL, 7);
	GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return true;
}
void VsmGeneratePass::UseShadowMap(std::shared_ptr<ShaderBase> program)
{
	auto textureID = glGetUniformLocation(program->GetID(), "shadow_map");
	glActiveTexture(GL_TEXTURE0 + 18);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(textureID, 18);
}
void VsmGeneratePass::SetLightSpaceMatrixUniform(std::shared_ptr<ShaderBase> program, int shadowType, int shadowLightSize) const
{
	glUniformMatrix4fv(glGetUniformLocation(program->GetID(), "LightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
	GLuint shadowLightPosID = glGetUniformLocation(program->GetID(), "shadow_light_pos");
	glUniform3fv(shadowLightPosID, 1, &pos[0]);

	GLuint shadowTypeID = glGetUniformLocation(program->GetID(), "shadow_type");
	glUniform1i(shadowTypeID, shadowType);

	GLuint shadowLightSizeID = glGetUniformLocation(program->GetID(), "shadow_light_size");
	glUniform1i(shadowLightSizeID, shadowLightSize);
}

void VsmGeneratePass::Render(std::shared_ptr<ShaderBase> program) const
{
	glViewport(0, 0, width, height);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glClear(GL_COLOR_BUFFER_BIT);
	SetLightSpaceMatrixUniform(program, 2, 2);
}