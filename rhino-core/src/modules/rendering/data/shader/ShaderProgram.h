#pragma once

#include <unordered_map>
#include <string>
#include <GLEW\GL\glew.h>
#include <fstream>
#include <sstream>

#include "utility/utility.h"
#include "UniformData.h"

namespace rhino {

	enum class ShaderProgramStatus {
		UNCOMPILED, COMPILE_ERROR, IDLE, RUNNING
	};

	class ShaderProgram {
		public:
			struct UniformPack {
				int location;
				bool needsMaterial;
				UniformData data;
			};

		private:

			unsigned int glId;
			// name, location, data
			std::unordered_map<std::string, UniformPack> uniforms;
			mutable ShaderProgramStatus status;
			mutable std::vector<const Texture*> loadedTextures;

			static bool readFile(const std::string& filePath, std::string& vertex, std::string& fragment, std::string& geometry, ShaderProgram& stm);
			static std::string finalizeShaderText(std::string source, const std::string& version);
			static void createProgram(const std::string& vertexSource, const std::string& fragmentSource, const std::string& geometrySource, ShaderProgram& stm);
			static unsigned int compileShader(const std::string& source, unsigned int type, const std::string& name);
			static bool checkForLinkingError(ShaderProgram& stm);

			static void prepareUniform(const std::string name, void* value, const UniformType& type, bool isDefault, ShaderProgram& stm);
			static void addAllUniforms(ShaderProgram& stm);
		public:
			ShaderProgram() :status(ShaderProgramStatus::UNCOMPILED) {}
			static ShaderProgram* compileProgram(const std::string& file);
			ShaderProgram(const ShaderProgram& other) = delete;

			~ShaderProgram();

			void loadBool(const std::string& name, const bool& value) const;
			void loadFloat(const std::string& name, const float& value) const;
			void loadDouble(const std::string& name, const double& value) const;
			void loadInt(const std::string& name, const int& value) const;
			void loadUInt(const std::string& name, const unsigned int& value) const;
			void loadVec2(const std::string& name, const Vector2& value) const;
			void loadVec3(const std::string& name, const Vector3& value) const;
			void loadVec4(const std::string& name, const Vector4& value) const;
			void loadColor(const std::string& name, const Color& value) const;
			void loadMat2(const std::string& name, const Matrix2& value) const;
			void loadMat3(const std::string& name, const Matrix3& value) const;
			void loadMat4(const std::string& name, const Matrix4& value) const;
			void loadTexture(const std::string& name, const Texture& value) const;

			void loadUniform(const std::string& name, UniformData::DataStorage data, const UniformType& type) const;

			void start() const;
			void stop() const;

			inline const std::unordered_map<std::string, UniformPack>& getUniformList() const { return uniforms; }
			inline const ShaderProgramStatus& getStatus() const { return status; }
	};
}