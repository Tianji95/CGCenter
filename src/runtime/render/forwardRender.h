#pragma once
#ifndef FORWARD_RENDER_H
#define FORWARD_RENDER_H

#include "render.h"
#include <memory>
#include "scene.h"
#include "depthpass.h"
#include "forward_main_pass.h"
#include "vsm_generate_pass.h"
#include "cubemappass.h"
namespace Zxen {
	class ForwardRender : public Render {
	public:
		ForwardRender(ZXEngine* engine) : Render(engine)
		{

		}
		virtual ~ForwardRender() = default;
		virtual void GenerateResources();
		virtual void UpdateRenderData();
		virtual void InsertGraphNode(RenderGraph* renderGraph);
		virtual void Draw();
	private:
		std::unique_ptr<CubemapPass> skyboxpass;
		std::shared_ptr<DepthPass> depthPass;
		std::shared_ptr<DepthPass> vsmPass;
		std::unique_ptr<ForwardMainPass> forwardMainPass;
	};
}
#endif // !FORWARD_RENDER_H
