#include "Material.h"

namespace rhino {

	Material::Material(ShaderProgram*& shader)
		:referenceShader(shader) {

		for (const auto& entry : shader->getUniformList()) {
			if (entry.second.needsMaterial) {
				values.insert({ entry.first, {entry.second.data.type, entry.second.data.value } });
			}
		}

	}

	Material::~Material() {
	}

	void Material::loadAll() const {
		if (referenceShader->getStatus() != ShaderProgramStatus::RUNNING) {
			std::cout << "Material loading error: reference shader is not running" << std::endl;
			return;
		}
		for (const auto& entry : values) {
			referenceShader->loadUniform(entry.first, entry.second.value, entry.second.type);
		}
	}
}