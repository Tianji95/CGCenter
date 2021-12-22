#pragma once
#ifndef SMART_PTR_H
#define SMART_PTR_H
#include <memory>

namespace Zxen {
	template<typename T>
	using SharePtr = std::shared_ptr<T>;

	template<typename T>
	using WeakPtr = std::weak_ptr<T>;

	template<typename T>
	using UniquePtr = std::unique_ptr<T>;

}

#endif // !SMART_PTR_H
