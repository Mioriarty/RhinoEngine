#include "Component.h"

namespace rhino { namespace ecs {

	std::vector<std::tuple<ComponentCreateFunction, ComponentFreeFunction, size_t>> BaseComponent::componentTypes;

	unsigned int BaseComponent::registerComponentType(ComponentCreateFunction createFun, ComponentFreeFunction freeFun, size_t size) {
		unsigned int componentId = componentTypes.size();
		componentTypes.push_back(std::tuple<ComponentCreateFunction, ComponentFreeFunction, size_t>(createFun, freeFun, size));
		return componentId;
	}

} }