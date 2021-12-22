#pragma once
#ifndef CUBEMAP_PASS_H
#define CUBEMAP_PASS_H
#include <string>
#include <vector>
#include <memory>
#include "renderpass.h"
#include "graphicNode.h"
#include "skybox.h"
namespace Zxen {
	class CubemapPass : public RenderPass {
	public:
		CubemapPass(ZXEngine* eng) : RenderPass(eng)
		{
		}
		~CubemapPass()
		{
		}
		void Render() override;
		bool GenResources();
		virtual void InsertGraphNode(RenderGraph* renderGraph);
		void UpdateRenderData();
	protected:
		std::unique_ptr<GraphicNode> node;
	private:
		SkyboxPtr skybox;
	};
}
#endif // !CUBEMAP_PASS_H
