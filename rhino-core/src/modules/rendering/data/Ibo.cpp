#include "Ibo.h"

#include <iostream>

#define ADD_OBJECT if(glId != 0) controller[glId]++
#define REMOVE_OBJECT if(glId != 0) if(--controller[glId] == 0) glDeleteBuffers(1, &glId)

namespace rhino {

	std::unordered_map<unsigned int, unsigned int> Ibo::controller;

	Ibo::Ibo(unsigned int glId, unsigned int count)
		:glId(glId), count(count) {
		ADD_OBJECT;
	}

	const Ibo& Ibo::operator=(const Ibo& ibo) {
		REMOVE_OBJECT;
		glId = ibo.glId;
		count = ibo.count;
		ADD_OBJECT;
		return *this;
	}

	Ibo Ibo::createIbo(const unsigned int* data, unsigned int count) {
		unsigned int glId;
		glGenBuffers(1, &glId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
		
		return Ibo(glId, count);
	}

	Ibo::~Ibo() {
		std::cout << "Delete Ibo. Crnt count " << controller.at(glId) << std::endl;
		REMOVE_OBJECT;
	}

	void Ibo::bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glId);
	}

	void Ibo::unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}

#undef ADD_OBEJCT
#undef REMOVE_OBJECT

