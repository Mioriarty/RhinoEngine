#include "Component.h"

#include "GameObject.h"

namespace rhino {



	void Component::attachToGameObject(GameObject* obj, bool isInGame) {
		gameObject = obj;
		inGame = isInGame;
	}

	void Component::detachFromGameObject() {
		gameObject = nullptr;
		if(inGame)
			remove();
	}

	std::string Component::toString() const {
		return typeid(*this).name();
	}

	Transform& Component::getTransform() {
		return gameObject->getTransform();
	}

}