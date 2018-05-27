#pragma once

#include <glew\GL\glew.h>
#include <GLFW\glfw3.h>
#include <unordered_map>

namespace rhino {
	class Vbo {
		private:
			unsigned int glId;

			Vbo(unsigned int glId);

		public:
			Vbo() = default;
			static Vbo createVbo(const void* data, unsigned int size);
			~Vbo();

			void bind() const;
			void unbind() const;

			inline unsigned int getGlId() const { return glId; }
	};
}
