#pragma once

#include <string>
#include <GLEW\GL\glew.h>

namespace rhino {

	struct TextureSettings {
		
		enum class FilterMode {
			NEAREST = GL_NEAREST,
			LINEAR = GL_LINEAR
		};

		enum class WrapMode {
			CLAMP = GL_CLAMP_TO_EDGE,
			REPEAT = GL_REPEAT,
			MIRRORED_REPEAT = GL_MIRRORED_REPEAT
		};

		FilterMode filterMode;
		WrapMode wrapHorizontal;
		WrapMode wrapVertical;
		bool mipmap;
		bool storeData;

		const static TextureSettings DEFAULT;

	};

	class Texture {

		private:
			unsigned int glId;
			int width, height, bpp;
			unsigned char* buffer;
			TextureSettings settings;

		public:
			Texture(const std::string& file, const TextureSettings& settings = TextureSettings::DEFAULT);
			~Texture();

			void bind(unsigned int slot = 0) const;
			void unbind() const;
	};
}