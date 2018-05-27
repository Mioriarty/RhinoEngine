#pragma once

#include "GameObject.h"

namespace rhino {

	class RootObject : public GameObject {

		protected:
			std::string name;

		public:
			RootObject();

			template<typename T>
			void addComponent(T* component);

			void deleteReferences();
	};


	template<typename T>
	inline void RootObject::addComponent(T* component) {
		static_assert(true, "A root object cannot contain components");
	}

}