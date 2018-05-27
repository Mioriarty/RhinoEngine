#include "VboLayout.h"

namespace rhino {

	VboLayout::VboLayout()
		: elements(std::vector<VboLayoutElement>()), stride(0) {
	}

	void VboLayout::pushFloat(unsigned int count) {
		elements.push_back({ GL_FLOAT, count, GL_FALSE });
		stride += getTypeSize(GL_FLOAT) * count;
	}

	void VboLayout::pushUInt(unsigned int count) {
		elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		stride += getTypeSize(GL_UNSIGNED_INT) * count;
	}

	void VboLayout::pushUChar(unsigned int count) {
		elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		stride += getTypeSize(GL_UNSIGNED_BYTE) * count;
	}
}