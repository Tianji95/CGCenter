#include "forward_main_pass.h"
#include "trianglemesh.h"
#include "rectanglemesh.h"
#include "program.h"
#include "depthpass.h"
#include "program.h"
#include "config.h"
#include "resourceManager.h"
#include "scene.h"
#include "zxEngine.h"
namespace Zxen {
	bool ForwardMainPass::GenResources()
	{
		ResourceManager* rsm = engine->GetResourceManager();
		prog = rsm->CreateProgram(SRC_BASE_PATH + "src/shaders/main.vert", SRC_BASE_PATH + "src/shaders/main.frag");
		prog->ProduceProgram();
		return true;
	}

	void ForwardMainPass::SetDepthPass(std::shared_ptr<DepthPass> depthpass)
	{
		depthPass = depthpass;
	}

	void ForwardMainPass::UpdateWindowSize(int display_w, int display_h)
	{
		windowWidth = display_w;
		windowHeight = display_h;
	}

	void ForwardMainPass::Render()
	{
		ResourceManager* rsm = engine->GetResourceManager();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, windowWidth, windowHeight);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		prog->use();
		{
			std::vector<AreaLightPtr> lights = rsm->GetAreaLights();
			for (auto light : lights) {
				light->SetUniforms(prog);
			}
		}
		{
			std::vector<PointLightPtr> lights = rsm->GetPointLights();
			for (auto light : lights) {
				light->SetUniforms(prog);
			}
		}

		{
			std::vector<SpotLightPtr> lights = rsm->GetSpotLights();
			for (auto light : lights) {
				light->SetUniforms(prog);
			}
		}


		depthPass->SetLightSpaceMatrixUniform(prog);
		auto textureID = glGetUniformLocation(prog->GetID(), "shadow_map");
		glActiveTexture(GL_TEXTURE0 + 18);
		glBindTexture(GL_TEXTURE_2D, depthPass->GetDepthTexture()->GetTextureID());
		glUniform1i(textureID, 18);

		std::vector<MeshPtr> meshes = rsm->GetRenderableMeshes();
		for (auto& mesh : meshes) {
			mesh->DrawElements(engine->GetScene()->GetCamera(), RenderPassType::FORWARD);
		}
		std::vector<RectangleMeshPtr> rectMeshes = rsm->GetAreaLightMeshes();
		for (auto mesh : rectMeshes) {
			mesh->DrawElements(engine->GetScene()->GetCamera(), RenderPassType::FORWARD);
		}
	}

	void ForwardMainPass::UpdateRenderData()
	{
		ResourceManager* rsm = engine->GetResourceManager();
		std::vector<MeshPtr> meshes = rsm->GetRenderableMeshes();
		for (auto& mesh : meshes) {
			mesh->UpdateProgram(RenderPassType::FORWARD, prog);
		}
	}

	void ForwardMainPass::InsertGraphNode(RenderGraph* renderGraph)
	{
		renderGraph->InsertGraphNode(*node);
	}
}