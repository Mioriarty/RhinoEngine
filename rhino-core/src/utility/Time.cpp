#include "Time.h"

#include <iostream>
#include <GLFW\glfw3.h>

namespace rhino {

	double Time::scaledGameTime = 0.0f;
	double Time::timeScale = 1.0f;
	double Time::deltaTime = 0.0;
	double Time::frameStart = 0.0f;

	void Time::startGame() {
		glfwSetTime(0.0);
	}

	void Time::startNewFrame() {
		double now = glfwGetTime();
		deltaTime = now - frameStart;
		scaledGameTime += deltaTime * timeScale;
		frameStart = now;
	}

	double Time::getTime() {
		return scaledGameTime;
	}

	double Time::getUnscaledTime() {
		return glfwGetTime();
	}

	double Time::getDeltaTime() {
		return deltaTime * timeScale;
	}

	double Time::getUnscaledDeltaTime() {
		return deltaTime;
	}

	void Time::setTimeScale(double scale) {
		timeScale = scale;
	}



}