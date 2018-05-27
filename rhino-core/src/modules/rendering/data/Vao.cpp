#include "Vao.h"

#include <iostream>

#define ADD_OBJECT if(glId != 0) controller[glId]++
#define REMOVE_OBJECT if(glId != 0) if(--controller[glId] == 0) glDeleteVertexArrays(1, &glId)

namespace rhino {

	std::unordered_map<unsigned int, unsigned int> Vao::controller;

	Vao::Vao(unsigned int glId)
		:glId(glId), vboCount(0) {
		ADD_OBJECT;
	}

	Vao Vao::createVao() {
		unsigned int glId;
		glGenVertexArrays(1, &glId);
		return Vao(glId);
	}

	Vao::~Vao(){
		std::cout << "Delete Vao (ID: " << glId << "). Crnt count " << controller.at(glId) << std::endl;
		REMOVE_OBJECT;

	}

	const Vao& Vao::operator=(const Vao& other) {
		REMOVE_OBJECT;
		glId = other.glId;
		ADD_OBJECT;
		return *this;
	}

	void Vao::bind() const {
		glBindVertexArray(glId);
		for (unsigned int i = 0; i < vboCount; i++)
			glEnableVertexAttribArray(i);
	}

	void Vao::unbind() const {
		for (unsigned int i = 0; i < vboCount; i++)
			glDisableVertexAttribArray(i);
		glBindVertexArray(0);
	}

	void Vao::addBuffer(const Vbo& vbo, const VboLayout& layout) {
		vboCount++;
		bind();
		vbo.bind();
		const std::vector<VboLayoutElement>& elements = layout.getElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++) {
			const VboLayoutElement& element = elements[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*) offset);
			offset += element.count * VboLayout::getTypeSize(element.type);
		}
		//vbo.unbind();

	}

}

#undef ADD_OBEJCT
#undef REMOVE_OBJECT