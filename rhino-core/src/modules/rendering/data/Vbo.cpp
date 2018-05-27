#include "Vbo.h"

#include <iostream>

namespace rhino {


	Vbo::Vbo(unsigned int glId)
		:glId(glId) {
	}

	Vbo Vbo::createVbo(const void* data, unsigned int size) {
		unsigned int glId;
		glGenBuffers(1, &glId);
		glBindBuffer(GL_ARRAY_BUFFER, glId);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		return Vbo(glId);
	}

	Vbo::~Vbo() {
		std::cout << "VBO DELETED" << std::endl;
		//glDeleteBuffers(1, &glId);
	}

	void Vbo::bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, glId);
	}

	void Vbo::unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}

