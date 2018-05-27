#pragma once

#include "utility\interfaces\IPrintable.h"

namespace rhino {

	class Color : public IPrintable {
		private:
			float r, g, b, a;

		public:
			Color();
			Color(float r, float g, float b, float a = 1.0f);

			inline float getR() const { return r; }
			inline float getG() const { return g; }
			inline float getB() const { return b; }
			inline float getA() const { return a; }

			std::string toString() const;

			static const Color BLACK;
			static const Color WHITE;
			static const Color GRAY;
			static const Color LIGHT_GRAY;
			static const Color DARK_GRAY;

			static const Color RED;
			static const Color GREEN;
			static const Color BLUE;

			static const Color YELLOW;
			static const Color CYAN;
			static const Color MAGENTA;
	};
}