#pragma once

#include "Vbo.h"
#include "VboLayout.h"

namespace rhino {

	class Vao {
		private:
			unsigned int glId;
			unsigned int vboCount;

			Vao(unsigned int glId);

			static std::unordered_map<unsigned int, unsigned int> controller;

		public:
			Vao() = default;
			static Vao createVao();
			~Vao();

			const Vao& operator=(const Vao& other);
			Vao(const Vao& other) { operator=(other); }

			void bind() const;
			void unbind() const;

			void addBuffer(const Vbo& vbo, const VboLayout& layout);

			inline unsigned int getGlId() const { return glId; }
	};
}

