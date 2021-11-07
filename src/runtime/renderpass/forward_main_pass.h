#pragma once
#ifndef FORWARD_MAIN_PASS_H
#define FORWARD_MAIN_PASS_H

#include "renderpass.h"

class ForwardMainPass : public RenderPass {
public:
	ForwardMainPass() = default;
	virtual ~ForwardMainPass() = default;
	virtual bool GenResources() override;
	virtual void Render() const;
protected:
private:
};


#endif // !FORWARD_MAIN_PASS_H
