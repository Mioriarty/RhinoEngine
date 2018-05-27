#include "Input.h"

#define MAX_INPUTS 1024

#include <iostream>

namespace rhino {

	Input::KeyState Input::status[MAX_INPUTS];
	float Input::mouseX;
	float Input::mouseY;
	float Input::scrollX;
	float Input::scrollY;

	std::stack<int> Input::changedStates;


	void Input::_keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		switch (action) {
			case GLFW_RELEASE:
				changedStates.push(key);
				status[key] = Input::KeyState::JUST_RELEASED;
				break;
			case GLFW_PRESS:
				changedStates.push(key); 
				status[key] = Input::KeyState::JUST_PRESSED;
				break;
			case GLFW_REPEAT:
				status[key] = Input::KeyState::LONG_PRESSED;
				break;
		}
	}

	void Input::_curserPosCallback(GLFWwindow* window, double x, double y) {
		mouseX = (float)x;
		mouseY = (float)y;
	}

	void Input::_mouseButtonCallback(GLFWwindow* window, int key, int action, int mods) {
		_keyCallback(window, key, -1, action, mods);
	}

	void Input::_scrollCallback(GLFWwindow* window, double x, double y) {
		std::cout << x << y << std::endl;
		scrollX = (float)x;
		scrollY = (float)y;
	}

	void Input::init() {
		GLFWwindow* w = glfwGetCurrentContext();
		glfwSetKeyCallback(w, Input::_keyCallback);
		glfwSetCursorPosCallback(w, Input::_curserPosCallback);
		glfwSetMouseButtonCallback(w, Input::_mouseButtonCallback);
		glfwSetScrollCallback(w, Input::_scrollCallback);
	}

	void Input::frameCleanUp() {
		while (!changedStates.empty()) {
			int key = changedStates.top();
			switch (status[key]) {
				case Input::KeyState::JUST_PRESSED: status[key] = Input::KeyState::PRESSED; break;
				case Input::KeyState::JUST_RELEASED: status[key] = Input::KeyState::RELEASED; break;
			}
			changedStates.pop();
		}

		scrollX = 0.0f;
		scrollY = 0.0f;
	}

	Input::KeyState Input::getKeyState(Input::Key key) {
		return status[(unsigned int)key];
	}

	float* Input::getCurserPos() {
		float stm[] = { mouseX, mouseY };
		return stm;
	}

	float* Input::getScroll() {
		float stm[] = { scrollX, scrollY };
		return stm;
	}

	void Input::getCurserPos(float& x, float& y) {
		x = mouseX;
		y = mouseY;
	}

	void Input::getScroll(float& x, float& y) {
		x = scrollX;
		y = scrollY;
	}

	bool Input::isKeyPressed(Key key) {
		Input::KeyState& state = status[(unsigned int)key];
		return state == Input::KeyState::PRESSED ||
			state == Input::KeyState::JUST_PRESSED ||
			state == Input::KeyState::LONG_PRESSED;
	}



}