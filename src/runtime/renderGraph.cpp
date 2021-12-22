#include "renderGraph.h"
namespace Zxen {
	void RenderGraph::InsertGraphNode(GraphNode& node)
	{
		nodes.push_back(&node);
	}

	void RenderGraph::Submit() const
	{
		for (auto& node : nodes) {
			node->Submit();
		}
	}

	void RenderGraph::Execute() const
	{
		for (auto& node : nodes) {
			node->Execute();
		}
	}
}