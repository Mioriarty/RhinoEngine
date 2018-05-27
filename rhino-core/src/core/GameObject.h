#pragma once

#include "../maths/maths.h"
#include "Component.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <list>

namespace rhino {

	class ObjectBehavior;

	class GameObject : public IPrintable {

		private:
			bool inGame;
			bool componentsOnHeap;

		protected:
			void awake();

			std::string name;
			Transform transform;

			GameObject* parent;
			std::vector<GameObject*> children;
			std::unordered_map<std::type_index, std::vector<Component*>> components;
			std::list<std::type_index> behaviorTypes;

			GameObject(const GameObject& other);

		public:
			GameObject(const std::string& name = "New Object", bool componentsOnHeap = false);
			~GameObject();
			
			template<typename T>
			void addComponent(T* component);

			template<typename T>
			void addComponent(const T& component);

			template<typename T>
			T* getComponent() const;

			template<typename T>
			const std::vector<T*> getComponents() const;

			GameObject* getChild(unsigned int index = 0);

			void update();
			void physicsUpdate();
			void lateUpdate();

			bool isAttached() const;

			void addAsChild(GameObject* obj);

			std::string toString() const;

			inline const std::string& getName() const { return name; } 
			inline void setName(const std::string& s) { name = s; }

			inline const Transform& getTransform() const { return transform; }
			inline Transform& getTransform() { return transform; }

			inline bool areComponentsOnHeap() const { return componentsOnHeap; }

			static GameObject* instantiate(const GameObject& obj);
	};

	template<typename T>
	void GameObject::addComponent(T* component) {
		static_assert(std::is_base_of<rhino::Component, T>::value, "You are trying to add a class to a game object which is not a component");
		if (inGame) {
			std::cerr << "You cannot modify game objects which are already instantiated!" << std::endl;
			return;
		}
		std::type_index index(typeid(T));
		Component* comp = (Component*)component;
		comp->attachToGameObject(this, inGame);

		if (components.find(index) == components.end()) {
			std::vector<Component*> v = { comp };
			components.insert({ index, v });

			if (std::is_base_of<rhino::ObjectBehavior, T>::value)
				behaviorTypes.push_back(index);

		} else {
			components[index].push_back(comp);
		}

		

	}

	template<typename T>
	inline void GameObject::addComponent(const T& component) {
		addComponent<T>((T*)&component);
	}

	template<typename T>
	T* GameObject::getComponent() const {
		const auto& it = components.find(std::type_index(typeid(T)));
		if (it == components.end())
			return nullptr;
		return (T*)it->second[0];
	}

	template<typename T>
	const std::vector<T*> GameObject::getComponents() const {
		const auto& it = components.find(std::type_index(typeid(T)));
		if (it == components.end())
			return {};
		
		std::vector<T*> stm;
		for (Component* comp : it->first) {
			stm.push_back((T*)comp);
		}

		return stm;
	}

}