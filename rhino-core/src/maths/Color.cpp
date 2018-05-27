#include "Color.h"
#include "Color.h"

namespace rhino {

	Color::Color()
		:r(1.0f), g(1.0f), b(1.0f), a(1.0f) {
	}


	Color::Color(float r, float g, float b, float a)
		: r(r), g(g), b(b), a(a) {
	}

	std::string Color::toString() const {
		return "Col[" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ", " + std::to_string(a) + "]";
	}

	const Color Color::BLACK =		Color(0.0f, 0.0f, 0.0f);
	const Color Color::WHITE =		Color(1.0f, 1.0f, 1.0f);
	const Color Color::GRAY =		Color(0.4f, 0.4f, 0.4f);
	const Color Color::LIGHT_GRAY =	Color(0.6f, 0.6f, 0.6f);
	const Color Color::DARK_GRAY =	Color(0.2f, 0.2f, 0.2f);

	const Color Color::RED =		Color(1.0f, 0.0f, 0.0f);
	const Color Color::GREEN =		Color(0.0f, 1.0f, 0.0f);
	const Color Color::BLUE =		Color(0.0f, 0.0f, 1.0f);

	const Color Color::YELLOW =		Color(1.0f, 1.0f, 0.0f);
	const Color Color::CYAN =		Color(0.0f, 1.0f, 1.0f);
	const Color Color::MAGENTA =	Color(1.0f, 0.0f, 1.0f);

}