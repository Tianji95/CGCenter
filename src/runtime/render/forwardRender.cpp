#include "forwardRender.h"
#include "resourceManager.h"
#include "PointLight.h"
#include "spotlight.h"
#include "arealight.h"
#include "config.h"
#include "program.h"

namespace Zxen {
	void ForwardRender::GenerateResources()
	{
		skyboxpass = std::make_unique<CubemapPass>(engine);
		skyboxpass->GenResources();

		vsmPass = std::make_shared<VsmGeneratePass>(engine, 1024, 1024);
		vsmPass->Setup(glm::vec3(4708.0f, 2842.0f, 2200.0f), glm::vec3(4708.0f, 2840.0f, 2200.0f), glm::vec3(1.0f), glm::vec4(-2000.0f, 2000.0f, -2000.0f, 2000.0f), 0.1f, 10000.0f);
		vsmPass->GenResources();

		forwardMainPass = std::make_unique<ForwardMainPass>(engine, windowWidth, windowHeight);
		forwardMainPass->GenResources();
	}

	void ForwardRender::UpdateRenderData()
	{
		if (vsmPass != nullptr) {
			vsmPass->SetShadowType(shadowType);
			vsmPass->SetShadowLightSize(shadowLightSize);
			vsmPass->UpdateRenderData();
		}
		if (forwardMainPass != nullptr) {
			forwardMainPass->SetDepthPass(vsmPass);
			forwardMainPass->UpdateRenderData();
		}
		if (skyboxpass != nullptr) {
			skyboxpass->UpdateRenderData();
		}
	}

	void ForwardRender::Draw()
	{
		if (vsmPass != nullptr) {
			vsmPass->Render();
		}
		if (forwardMainPass != nullptr) {
			forwardMainPass->UpdateWindowSize(windowWidth, windowHeight);
			forwardMainPass->Render();
		}
		if (skyboxpass != nullptr) {
			skyboxpass->Render();
		}
	}


	void ForwardRender::InsertGraphNode(RenderGraph* renderGraph)
	{
		if (skyboxpass != nullptr) {
			skyboxpass->InsertGraphNode(renderGraph);
		}
		if (vsmPass != nullptr) {
			vsmPass->InsertGraphNode(renderGraph);
		}
		if (forwardMainPass != nullptr) {
			forwardMainPass->InsertGraphNode(renderGraph);
		}
	}
}