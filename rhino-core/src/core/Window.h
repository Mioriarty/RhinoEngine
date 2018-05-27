#pragma once

#include <GLEW\GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <string>

namespace rhino {

	class Window {
	private:
		unsigned int width, height;
		std::string title;
		GLFWwindow* window;

		bool init();

		static void _windowResizeCallback(GLFWwindow* window, int width, int height);

	public:
		Window() = default;
		~Window();

		bool open(int width, int height, const std::string& title);

		bool isCloseRequested() const;
		void clear() const;
		void update() const;

		const unsigned int& getWidth() const { return width; };
		const unsigned int& getHeight() const { return height; };
	};

}
