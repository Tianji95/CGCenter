#include "entity/entitybase.h"
#include <type_traits>
namespace Zxen {
	template<typename T>
	void EntityBase::AddComponent(T* comp)
	{
		if (!std::is_base_of<Component, T>::value) {
			return;
		}
		components[typeid(T).name()] = comp;
	}

	template<typename T>
	T* EntityBase::GetComponent()
	{
		if (!std::is_base_of<Component, T>::value) {
			return nullptr;
		}
		if (components.find(typeid(T).name()) == components.end()) {
			return nullptr;
		}
		return components[typeid(T).name()];
	}
}