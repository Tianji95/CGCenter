#include "depthpass.h"
#include "glm/gtc/type_ptr.hpp"
#include "program.h"
#include "config.h"
#include "resourceManager.h"
#include "mesh.h"
#include "scene.h"
#include "zxEngine.h"
namespace Zxen {
	bool DepthPass::GenResources()
	{
		ResourceManager* rsm = engine->GetResourceManager();
		prog = rsm->CreateProgram(SRC_BASE_PATH + "src/shaders/simple_depth_map_generate.vert", SRC_BASE_PATH + "src/shaders/simple_depth_map_generate.frag");
		prog->ProduceProgram();
		material = rsm->CreateMaterial();
		material->program = prog;
		depthTexture = rsm->CreateTexture2D(std::string("shadowmap"));
		depthTexture->Setup(std::string("shadow_map"), width, height, 0, GL_DEPTH_COMPONENT32, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
		GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
		depthTexture->SetupBorderColor(borderColor);
		depthTexture->Submit();

		fb = rsm->CreateFrameBuffer();
		fb->AddAttachment(GL_DEPTH_ATTACHMENT, depthTexture);
		fb->Setup();
		fb->Submit();
		return true;
	}

	void DepthPass::Render()
	{
		ResourceManager* rsm = engine->GetResourceManager();
		prog->use();
		glUniformMatrix4fv(glGetUniformLocation(prog->GetID(), "LightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
		glViewport(0, 0, width, height);
		glBindFramebuffer(GL_FRAMEBUFFER, fb->GetFBID());
		glClear(GL_DEPTH_BUFFER_BIT);
		std::vector<MeshPtr> meshes = rsm->GetRenderableMeshes();
		for (auto& mesh : meshes) {
			mesh->DrawElements(engine->GetScene()->GetCamera(), RenderPassType::SHADOW);
		}
	}

	void DepthPass::SetLightSpaceMatrixUniform(std::shared_ptr<Program> program) const
	{
		glUniformMatrix4fv(glGetUniformLocation(program->GetID(), "LightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

		GLuint shadowLightPosID = glGetUniformLocation(program->GetID(), "shadow_light_pos");
		glUniform3fv(shadowLightPosID, 1, &pos[0]);

		GLuint shadowTypeID = glGetUniformLocation(program->GetID(), "shadow_type");
		glUniform1i(shadowTypeID, shadowType);

		GLuint shadowLightSizeID = glGetUniformLocation(program->GetID(), "shadow_light_size");
		glUniform1i(shadowLightSizeID, shadowLightSize);
	}

	void DepthPass::UpdateRenderData()
	{
		ResourceManager* rsm = engine->GetResourceManager();
		std::vector<MeshPtr> meshes = rsm->GetRenderableMeshes();
		for (auto& mesh : meshes) {
			mesh->AddMaterials(RenderPassType::SHADOW, material);
		}
	}

	void DepthPass::InsertGraphNode(RenderGraph* renderGraph)
	{
		renderGraph->InsertGraphNode(*node);
	}

	Texture2DPtr DepthPass::GetDepthTexture()
	{
		return depthTexture;
	}

	void DepthPass::SetShadowType(unsigned int type)
	{
		shadowType = type;
	}

	void DepthPass::SetShadowLightSize(unsigned int lightsize)
	{
		shadowLightSize = lightsize;
	}
}