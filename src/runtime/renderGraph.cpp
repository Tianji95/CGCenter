#include "renderGraph.h"

void RenderGraph::InsertGraphNode(GraphNode* node)
{
	nodes.push_back(node);
}

void RenderGraph::Submit()
{
	for (auto& node : nodes) {
		node->Submit();
	}
}

void RenderGraph::Execute()
{
	for (auto& node : nodes) {
		node->Execute();
	}
}
