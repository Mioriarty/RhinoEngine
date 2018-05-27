#include "GameObject.h"

#include "Application.h"


namespace rhino {


	GameObject::GameObject(const std::string& name, bool componentsOnHeap)
		:name(name), parent(nullptr), inGame(false), componentsOnHeap(componentsOnHeap) {
	}

	GameObject::GameObject(const GameObject& other)
		:name(other.name), parent(nullptr), inGame(false), transform(other.transform), behaviorTypes(other.behaviorTypes), 
			componentsOnHeap(true) {

		for (auto& itIndex : other.components) {
			std::vector<Component*> v;
			v.reserve(itIndex.second.size());

			for (auto& itComp : itIndex.second) {
				Component* c = itComp->getCopy();
				c->attachToGameObject(this, false);
				v.emplace_back(c);
			}

			components[itIndex.first] = v;
		}

		children.reserve(other.children.size());

		for (auto& itObj : other.children)
			children.emplace_back(new GameObject(*itObj));

	}

	GameObject::~GameObject() {
		if(componentsOnHeap)
			for (auto& entry : components) {
				for (Component* c : entry.second) {
					c->detachFromGameObject();

					delete c;
				}
			}


		for (GameObject* obj : children)
			delete obj;

		components.clear();
		children.clear();

	}

	void GameObject::awake() {
		for (auto& entry : components) {
			for (Component* c : entry.second) {
				c->awake();
			}
		}
		for (GameObject* o : children) {
			o->awake();
		}
	}


	void GameObject::update() {
		for (auto& entry : components) {
			for (Component* c : entry.second) {
				c->update();
			}
		}
		for (GameObject* o : children) {
			o->update();
		}
	}

	void GameObject::physicsUpdate() {
		for (auto& entry : components) {
			for (Component* c : entry.second) {
				c->physicsUpdate();
			}
		}
		for (GameObject* o : children) {
			o->physicsUpdate();
		}
	}

	void GameObject::lateUpdate() {
		for (auto& entry : components) {
			for (Component* c : entry.second) {
				c->lateUpdate();
			}
		}

		for (GameObject* o : children) {
			o->lateUpdate();
		}
	}

	GameObject* GameObject::getChild(unsigned int index) {
		return children[index];
	}

	std::string GameObject::toString() const {
		return "GameObject: " + name;
	}

	bool GameObject::isAttached() const {
		return parent != nullptr;
	}

	void GameObject::addAsChild(GameObject* obj) {
		obj->parent = this;
		children.push_back(obj);
	}


	GameObject* GameObject::instantiate(const GameObject& obj) {
		GameObject* stm = new GameObject(obj);
		stm->inGame = true;
		stm->awake();
		Application::addGameObject(stm);
		return stm;
	}

}