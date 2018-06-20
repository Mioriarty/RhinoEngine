#ifndef RHINO_COMPONENT_H
#define RHINO_COMPONENT_H


#include "utility\interfaces\IPrintable.h"
#include "maths\maths.h"

#define SIMPLE_GETCOPY_OVERLOAD(TYPE) public: Component* getCopy() const override {return new TYPE(*this);}

namespace rhino {

	class GameObject;

	class Component : public IPrintable {

		friend class rhino::GameObject;

		private:
			void detachFromGameObject();
			void attachToGameObject(GameObject* obj, bool isInGame);

			bool inGame;
		
		public:

			virtual void awake() {};
			virtual void update() {};
			virtual void physicsUpdate() {};
			virtual void lateUpdate() {};
			virtual void remove() {};

			virtual Component* getCopy() const = 0;

			GameObject* gameObject;

			inline GameObject* getGameObject() const { return gameObject; }
			Transform& getTransform();

			virtual std::string toString() const;

	};

}

#endif // !RHINO_COMPONENT_H