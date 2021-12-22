#pragma once
#ifndef RENDER_GRAPH_H
#define RENDER_GRAPH_H
#include "graphNode.h"
#include <list>
namespace Zxen {
	class RenderGraph {
	public:
		RenderGraph() = default;
		~RenderGraph() = default;
		void InsertGraphNode(GraphNode& node);
		void Execute() const;
		void Submit() const;
	private:
		std::list<GraphNode*> nodes;
	};
}
#endif // !RENDER_GRAPH_H
