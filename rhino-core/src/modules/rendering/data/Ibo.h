#pragma once

#include <glew\GL\glew.h>
#include <GLFW\glfw3.h>
#include <unordered_map>

namespace rhino {
	class Ibo {
		private:
			unsigned int glId;
			unsigned int count;

			Ibo(unsigned int glId, unsigned int count);

			static std::unordered_map<unsigned int, unsigned int> controller;

		public:
			Ibo() = default;

			const Ibo& operator=(const Ibo& other);
			Ibo(const Ibo& other) { operator=(other); }
			
			static Ibo createIbo(const unsigned int* data, unsigned int count);
			~Ibo();

			void bind() const;
			void unbind() const;

			inline unsigned int getGlId() const { return glId; }
			inline unsigned int getCount() const { return count; }
	};
}
