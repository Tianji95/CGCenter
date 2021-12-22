#pragma once
#ifndef RENDERABLE_COMPONENT_H
#define RENDERABLE_COMPONENT_H
#include "component/component.h"
#include "mesh.h"
namespace Zxen {
	class RenderableComponent : public Component {
	public:
		RenderableComponent() = default;
		virtual ~RenderableComponent() = default;
	private:
		Mesh* mesh;

	};
}
#endif // !RENDERABLE_COMPONENT_H
