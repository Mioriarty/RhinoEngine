#include "RootObject.h"

namespace rhino {

	RootObject::RootObject()
		:name("Root Object") {
	}

	void RootObject::deleteReferences() {

		for (GameObject* obj : children)
			delete obj;

		children.clear();

	}

}