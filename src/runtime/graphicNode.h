#pragma once
#ifndef GRAPHIC_NODE_H
#define GRAPHIC_NODE_H
#include "graphNode.h"
#include "program.h"
namespace Zxen {
	class GraphicNode : public GraphNode {
	public:
		GraphicNode() = default;
		~GraphicNode() = default;
		virtual void Submit() override;
		virtual void Execute() override;
	private:
	};

}
#endif // !GRAPHIC_NODE_H
