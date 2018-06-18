#pragma once

#include "Component.h"

namespace rhino { namespace ecs {

	class BaseSystem {

		private:
			std::vector<unsigned int> componentTypes;

		public:
			BaseSystem(const std::vector<unsigned int>& componentTypes)
				: componentTypes(componentTypes) {
			}

			virtual void updateComponents(BaseComponent** components) {};

			inline const std::vector<unsigned int>& getComponentTypes() const { return componentTypes; }

	};


}}
