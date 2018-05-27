 #include "Application.h"

#include <iostream>
#include "Graphics.h"

namespace rhino {

	Window						Application::window;
	RootObject					Application::root;
	Application::AppProperties	Application::properties;

	std::stack<std::pair<bool(*)(), std::string>> Application::initFunctions;
	std::list<void(*)()>						  Application::updateFunctions;
	std::list<void(*)()>						  Application::renderFunctions;
	std::list<void(*)()>						  Application::physicsFunctions;
	std::list<void(*)()>						  Application::lateUpdateFunctions;

	void Application::start(const AppProperties& props, bool(*loadFunc)(), void(*updateFunc)()) {
		properties = props;
		if(updateFunc != nullptr)
			updateFunctions.push_back(updateFunc);

		if (!window.open(props.width, props.height, props.name)) {
			std::cerr << "Couldn't open the window" << std::endl;
			return;
		}

		Graphics::width = props.width;
		Graphics::height = props.height;

		if (!doInitFunctions(loadFunc)) {
			free(&window);
			return;
		}

		gameLoop();
		root.deleteReferences();
	}

	bool Application::doInitFunctions(bool(*loadFunc)()) {
		while (!initFunctions.empty()) {
			auto& e = initFunctions.top();
			if (!e.first()) {
				std::cerr << "Failed to initialize the '" + e.second + "' module!" << std::endl;
				initFunctions = std::stack<std::pair<bool(*)(), std::string>>();
				return false;
			}
			initFunctions.pop();
		}

		if (!loadFunc()) {
			std::cerr << "The load function failed" << std::endl;
			return false;
		}

		return true;
	}

	void Application::gameLoop() {
		while (!window.isCloseRequested()) {
			window.clear();
				
			update();
			physicsUpdate();
			lateUpdate();
			render();

			window.update();
		}
	}

	void Application::update() {
		for (void(*fun)() : updateFunctions)
			fun();

		root.update();
	}

	void Application::physicsUpdate() {
		for (void(*fun)() : physicsFunctions)
			fun();

		root.physicsUpdate();
	}

	void Application::lateUpdate() {
		for (void(*fun)() : lateUpdateFunctions)
			fun();

		root.lateUpdate();
	}

	void Application::render() {
		for (void(*fun)() : renderFunctions)
			fun();
	}


	void Application::addGameObject(GameObject* obj) {
		root.addAsChild(obj);
	}

	void Application::loadModule(const Module& module) {
		if (module.init != nullptr)
			initFunctions.push({ module.init, module.name });

		if (module.update != nullptr)
			updateFunctions.push_back(module.update);

		if (module.render != nullptr)
			renderFunctions.push_back(module.render);

		if(module.physicsUpdate != nullptr)
			physicsFunctions.push_back(module.physicsUpdate);

		if(module.lateUpdate != nullptr)
			lateUpdateFunctions.push_back(module.lateUpdate);
	}

}