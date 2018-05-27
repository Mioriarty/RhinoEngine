#include "Window.h"
#include "../utility/Time.h"
#include "../utility/Input.h"
#include "Graphics.h"


namespace rhino {


	Window::~Window() {
		glfwTerminate();
	}

	bool Window::open(int width, int height, const std::string& title) {
		this->width = width;
		this->height = height;
		this->title = title;
		if (!init()) {
			glfwTerminate();
			return false;
		}
		Input::init();
		return true;
	}

	bool Window::init() {
		if (!glfwInit()) {
			std::cout << "Failed to initialize GLFW!" << std::endl;
			return false;
		}

		window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (!window) {
			std::cout << "Failed to Create GLFW window!" << std::endl;
			return false;
		}

		glfwMakeContextCurrent(window);
		glfwSetWindowSizeCallback(window, Window::_windowResizeCallback);


		if (glewInit() != GLEW_OK) {
			std::cout << "Failed to initialize GLEW!" << std::endl;
			return false;
		}

		std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;
		Time::startGame();

		return true;
	}

	bool Window::isCloseRequested() const {
		return glfwWindowShouldClose(window) == 1;
	}

	void Window::clear() const {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Time::startNewFrame();
	}

	void Window::update() const {
		Input::frameCleanUp();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void Window::_windowResizeCallback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		Graphics::height = height;
		Graphics::width = width;
		
	}

}

