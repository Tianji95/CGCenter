#pragma once
#ifndef RENDER_PASS_H
#define RENDER_PASS_H

class RenderPass {
public:
	RenderPass() = default;
	virtual ~RenderPass() = default;
	virtual bool GenResources() = 0;
protected:
private:
};

#endif // !RENDER_PASS_H
