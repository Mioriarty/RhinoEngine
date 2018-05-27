#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#define ABSOLUTE_PATH "C:/Users/Moritz/Desktop/Programmieren/C++/RhinoEngine/rhino-core/"
#include <stb_image.h>
#include <iostream>

namespace rhino {

	const TextureSettings TextureSettings::DEFAULT = {TextureSettings::FilterMode::LINEAR, TextureSettings::WrapMode::CLAMP, TextureSettings::WrapMode::CLAMP, true, false};

	Texture::Texture(const std::string& file, const TextureSettings& settings) 
		:settings(settings) {

		stbi_set_flip_vertically_on_load(1);

		buffer = stbi_load((ABSOLUTE_PATH + file).c_str(), &width, &height, &bpp, 4);

		if (buffer == nullptr) {
			std::cout << "stb_image couldn't read the image (" << file << ")" << std::endl;
			return;
		}


		glGenTextures(1, &glId);
		glBindTexture(GL_TEXTURE_2D, glId);

		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (int)settings.filterMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int)settings.filterMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (int)settings.wrapHorizontal);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (int)settings.wrapVertical);



		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)buffer);

		glBindTexture(GL_TEXTURE_2D, 0);

		if (!settings.storeData)
			stbi_image_free(buffer);

	}

	Texture::~Texture() {
		glDeleteTextures(1, &glId);
	}

	void Texture::bind(unsigned int slot) const {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, glId);
	}

	void Texture::unbind() const {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}