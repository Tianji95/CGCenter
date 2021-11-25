#pragma once
#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

class GraphNode {
public:
	GraphNode() = default;
	~GraphNode() = default;

	virtual void Submit() = 0;
	virtual void Execute() = 0;
};
#endif // !RENDER_PASS_NODE_H
