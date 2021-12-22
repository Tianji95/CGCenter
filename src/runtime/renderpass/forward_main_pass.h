#pragma once
#ifndef FORWARD_MAIN_PASS_H
#define FORWARD_MAIN_PASS_H

#include "renderpass.h"
#include "graphicNode.h"
#include "depthpass.h"
namespace Zxen {
	class ZXEngine;
	class ForwardMainPass : public RenderPass {
	public:
		ForwardMainPass(ZXEngine* eng, GLint windowWidth, GLint windowHeight) : RenderPass(eng), windowWidth(windowWidth), windowHeight(windowHeight)
		{
		}
		virtual ~ForwardMainPass() = default;
		virtual bool GenResources() override;
		virtual void Render() override;
		virtual void InsertGraphNode(RenderGraph* renderGraph) override;
		virtual void UpdateRenderData();
		void SetDepthPass(std::shared_ptr<DepthPass> depthpass);
		void UpdateWindowSize(int display_w, int display_h);
	protected:
	private:
		MaterialPtr material;
		ProgramPtr prog;
		GLint windowWidth = 1024;
		GLint windowHeight = 1024;
		std::unique_ptr<GraphicNode> node;
		std::shared_ptr<DepthPass> depthPass;
	};
}

#endif // !FORWARD_MAIN_PASS_H
