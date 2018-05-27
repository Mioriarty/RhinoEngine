#pragma once

#include <vector>
#include <GLEW\GL\glew.h>

namespace rhino {

	struct VboLayoutElement {
		unsigned int type;
		unsigned int count;
		unsigned int normalized;
	};

	class VboLayout {
		
		private:
			std::vector<VboLayoutElement> elements;
			unsigned int stride;

		public:
			VboLayout();

			void pushFloat(unsigned int count);
			void pushUInt(unsigned int count);
			void pushUChar(unsigned int count);

			inline unsigned int getStride() const { return stride; }
			inline const std::vector<VboLayoutElement>& getElements() const { return elements; }

			static unsigned int getTypeSize(const unsigned int type) {
				switch (type) {
					case GL_FLOAT:			return sizeof(GLfloat);
					case GL_UNSIGNED_INT:	return sizeof(GLuint);
					case GL_UNSIGNED_BYTE:	return sizeof(GLubyte);
					default: return 0;
				}
			}
	};
}
