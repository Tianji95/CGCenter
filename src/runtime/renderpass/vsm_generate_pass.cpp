#include "vsm_generate_pass.h"
#include "glm/gtc/type_ptr.hpp"
#include "config.h"
#include "resourceManager.h"
#include "mesh.h"
#include "zxEngine.h"
#include "scene.h"
namespace Zxen {
	bool VsmGeneratePass::GenResources()
	{
		ResourceManager* rsm = engine->GetResourceManager();;
		prog = rsm->CreateProgram(SRC_BASE_PATH + "src/shaders/vsm_generate.vert", SRC_BASE_PATH + "src/shaders/vsm_generate.frag");
		prog->ProduceProgram();
		material = rsm->CreateMaterial();
		material->program = prog;

		// node->SetProgram(prog);
		depthTexture = rsm->CreateTexture2D(std::string("shadowmap"));
		depthTexture->Setup(std::string("shadow_map"), width, height, 0, GL_RG32F, GL_RG, GL_FLOAT, nullptr);
		GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
		depthTexture->SetupBorderColor(borderColor);
		depthTexture->Submit();

		fb = rsm->CreateFrameBuffer();
		fb->AddAttachment(GL_COLOR_ATTACHMENT0, depthTexture);
		fb->Setup();
		fb->Submit();
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return true;
	}

	void VsmGeneratePass::Render()
	{
		ResourceManager* rsm = engine->GetResourceManager();
		prog->use();
		glUniformMatrix4fv(glGetUniformLocation(prog->GetID(), "LightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
		glViewport(0, 0, width, height);
		glBindFramebuffer(GL_FRAMEBUFFER, fb->GetFBID());
		glClear(GL_COLOR_BUFFER_BIT);

		// todo 解耦program参数和draw()
		std::vector<MeshPtr> meshes = rsm->GetRenderableMeshes();
		for (auto& mesh : meshes) {
			mesh->DrawElements(engine->GetScene()->GetCamera(), RenderPassType::SHADOW);
		}
	}
}