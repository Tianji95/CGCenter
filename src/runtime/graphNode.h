#pragma once
#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H
#include "program.h"
namespace Zxen {
	class GraphNode {
	public:
		GraphNode() = default;
		~GraphNode() = default;
		virtual void Submit() = 0;
		virtual void Execute() = 0;
		virtual void SetProgram(ProgramPtr prog)
		{
			program = prog;
		}
	protected:
		ProgramPtr program;
	};
}
#endif // !RENDER_PASS_NODE_H
