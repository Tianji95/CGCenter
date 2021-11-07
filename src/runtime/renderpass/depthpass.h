#pragma once
#ifndef SHADOW_PASS_H
#define SHADOW_PASS_H
#include "renderpass.h"
#include <GL/glew.h>

class DepthPass : public RenderPass{
public:
	DepthPass() = default;
	virtual ~DepthPass() = default;
	virtual bool GenResources() override;
	virtual void Render() const;
protected:
private:
	GLuint depthMapFBO;
	GLuint width = 1024;
	GLuint height = 1024;
	GLuint texture = 0;
};

#endif // !SHADOW_PASS_H

