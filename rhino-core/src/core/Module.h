#pragma once

#include <string>

namespace rhino {


	struct Module {
		
		std::string name;

		bool(*init)();
		void(*update)();
		void(*physicsUpdate)();
		void(*lateUpdate)();
		void(*render)();

		

	};

}
