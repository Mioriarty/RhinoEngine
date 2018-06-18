#pragma once

#include <vector>
#include <tuple>

namespace rhino { namespace ecs {

	struct BaseComponent;

	typedef void* EntityHandle;
	typedef unsigned int (*ComponentCreateFunction)(std::vector<char>& memory, EntityHandle entity, BaseComponent* comp);
	typedef void(*ComponentFreeFunction)(BaseComponent* comp);


	struct BaseComponent {

		private:
			static std::vector<std::tuple<ComponentCreateFunction, ComponentFreeFunction, size_t>> componentTypes;

		public:
			static unsigned int registerComponentType(ComponentCreateFunction createFun, ComponentFreeFunction freeFun, size_t size);

			inline static ComponentCreateFunction getTypeCreateFunction(unsigned int id) { return std::get<0>(componentTypes[id]); }
			inline static ComponentFreeFunction getTypeFreeFunction(unsigned int id) { return std::get<1>(componentTypes[id]); }
			inline static size_t getTypeSize(unsigned int id) { return std::get<2>(componentTypes[id]); }
			inline static bool isTypeValid(unsigned int id) { return id < componentTypes.size(); }

			EntityHandle handle;

	};

	template<typename T>
	struct Component : public BaseComponent {
		static const ComponentCreateFunction createFunction;
		static const ComponentFreeFunction freeFunction;

		static const unsigned int id;
		static const size_t size;
	};

	template<typename T>
	unsigned int componentCreate(std::vector<char>& memory, EntityHandle entity, BaseComponent* comp) {
		unsigned int index = memory.size();
		memory.reserve(index + T::size);
		T* component = new(&memory[index]) T(*(T*)comp);
		component->entity = entity;
		return index;
	}

	template<typename T>
	unsigned int componentFree(BaseComponent* comp) {
		((T*)comp)->~T();
	}

	template<typename T>
	const ComponentCreateFunction Component<T>::createFunction = componentCreate;

	template<typename T>
	const ComponentFreeFunction Component<T>::freeFunction = componentFree;

	template<typename T>
	const unsigned int Component<T>::id = BaseComponent::registerComponentType(Component<T>::createFunction, Component<T>::freeFunction, sizeof(T));

	template<typename T>
	const size_t Component<T>::size = sizeof(T);


	// Test Code

	struct TestComponent : public Component<TestComponent> {
		float x, y;
	};


} }