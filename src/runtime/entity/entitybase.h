#pragma once
#ifndef ENTITY_BASE_H
#define ENTITY_BASE_H
#include <string>
#include <unordered_map>
#include "component/component.h"
namespace Zxen {
	class EntityBase {
	public:
		EntityBase() = default;
		~EntityBase() = default;
		template<typename T>
		void AddComponent(T* comp);

		template<typename T>
		T* GetComponent();
	protected:
		std::unordered_map<std::string, Component*> components;
	};
}
#endif // !ENTITY_BASE_H
