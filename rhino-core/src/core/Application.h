#pragma once

#include "RootObject.h"
#include "Module.h"

#define PLATFORM_DESCTOP

#ifdef PLATFORM_DESCTOP
 #include "Window.h"
#elif PLATFORM_ANDROID

#elif PLATFORM_IOS

#else
 #error No platform specified
#endif

#include <stack>

namespace rhino {

	class Application {

		friend class rhino::GameObject;

		public:
			struct AppProperties {
				std::string name;
				unsigned int width, height;
				std::string version;
			};


		private:
			static AppProperties properties;
			static Window window;
			static RootObject root;

			// *** MODULE STUFF ***
			static std::stack<std::pair<bool(*)(), std::string>>	initFunctions;
			static std::list<void(*)()>								updateFunctions;
			static std::list<void(*)()>								renderFunctions;
			static std::list<void(*)()>								physicsFunctions;
			static std::list<void(*)()>								lateUpdateFunctions;
			// *********************

			static bool doInitFunctions(bool(*loadFunc)());

			static void gameLoop();
			static void update();
			static void physicsUpdate();
			static void lateUpdate();
			static void render();

			static void addGameObject(GameObject* obj);


		public:
			Application() = delete;

			static void loadModule(const Module& module);

			static void start(const AppProperties& properties, bool (*loadFunc)(), void (*updateFunc)() = nullptr);

			static GameObject* getRoot() { return (GameObject*)&root; };


	};

}