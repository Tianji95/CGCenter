#pragma once
#ifndef RENDER_PASS_H
#define RENDER_PASS_H
#include "renderGraph.h"
namespace Zxen {
	class ZXEngine;
	class RenderPass {
	public:
		RenderPass(ZXEngine* eng) : engine(eng)
		{

		}
		virtual ~RenderPass() = default;
		virtual bool GenResources() = 0;
		virtual void InsertGraphNode(RenderGraph* renderGraph) = 0;
		virtual void UpdateRenderData() = 0;
		virtual void Render() = 0;
	protected:
		ZXEngine* engine = nullptr;
	private:
	};
}
#endif // !RENDER_PASS_H
