#pragma once
#ifndef DIRECT_LIGHT_H
#define DIRECT_LIGHT_H
#include "light.h"
namespace Zxen {
	class DirectLight : public Light {
	public:
		DirectLight() = default;
		virtual ~DirectLight() = default;
	private:

	};
}
#endif // !DIRECT_LIGHT_H
