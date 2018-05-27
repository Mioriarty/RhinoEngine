#include "ShaderProgram.h"

#include <iostream>

#define ABSOLUTE_PATH "C:/Users/Moritz/Desktop/Programmieren/C++/RhinoEngine/rhino-core/"

namespace rhino {


	ShaderProgram* ShaderProgram::compileProgram(const std::string& file) {
		std::string vertexSource, fragmentSource, geometrySource;
		ShaderProgram* stm = new ShaderProgram();

		if (!readFile(ABSOLUTE_PATH + file, vertexSource, fragmentSource, geometrySource, *stm)) {
			stm->status = ShaderProgramStatus::COMPILE_ERROR;
			return stm;
		}

		createProgram(vertexSource, fragmentSource, geometrySource, *stm);

		prepareUniform("viewMatrix", (void*)&Matrix4::identity(), UniformType::MAT4, false, *stm);
		prepareUniform("modelMatrix", (void*)&Matrix4::identity(), UniformType::MAT4, false, *stm);
		addAllUniforms(*stm);
		
		return stm;
	}

	ShaderProgram::~ShaderProgram() {
		glDeleteProgram(glId);
	}

	bool ShaderProgram::readFile(const std::string& filePath, std::string& vertex, std::string& fragment, std::string& geometry, ShaderProgram& stm) {
		std::fstream stream(filePath);
		std::stringstream ss[3];

		if (!stream.is_open()) {
			std::cout << "Couldn't open file: " << filePath << std::endl;
			return false;
		}

		enum ReadingMode {
			NONE = -1, VERTEX = 0, FRAGMENT = 1, GEOMETRY = 2
		};

		int mode = NONE;

		int lineCount = 0;
		std::string line;
		bool hasShader[3] = { false, false, false };
		std::string version;
		while (getline(stream, line)) {
			lineCount++;
			int found = line.find("##");
			if (found != std::string::npos) {
				std::vector<std::string> args = Utility::split(line.substr(found + 2), ' ');
				if (args[0] == "shader") {
					if (args[1] == "vertex") {
						hasShader[0] = true;
						mode = VERTEX;
					} else if (args[1] == "fragment") {
						hasShader[1] = true;
						mode = FRAGMENT;
					} else if (args[2] == "geometry") {
						hasShader[2] = true;
						mode = GEOMETRY;
					} else {
						std::cout << "Reading error: No supported shader specified (line " << lineCount << ": " << line << ")" << std::endl;
						return false;
					}
				} else if (args[0] == "set") {
					if (args[1] == "version") {
						version = "#version " + args[2];
						if (args.size() > 3)
							version += " " + args[3];
					}
				} else {
					std::cout << "Reading error: Unknown instruction: " << args[0] << " in line " << lineCount << std::endl;
					return false;
				}

			} else {
				if (mode >= VERTEX && mode <= GEOMETRY) {
					ss[mode] << line;
					int start = line.find("uniform ");
					if (start != std::string::npos) {
						// Creating the uniform variable
						start = (line.substr(start + 8)).find_first_not_of((const char)'\t ') + 8;
						int space = line.substr(start).find_first_of(' ') + start;
						int simicolon = line.substr(space).find_first_of((const char)' ;') + space;
						UniformType type = stringToUniformType(line.substr(start, space - start));
						std::string name = line.substr(space + 1, simicolon - space - 1);
						name = Utility::removeSpaces(name);
						if (type == UniformType::ERROR) {
							std::cout << "Reading error: Unknown uniform type '" << line.substr(start, space - start) << "' in line " << lineCount << std::endl;
							return false;
						}
						// CRAAAAAAPPPPP CODE
						int ccc = 0;
						prepareUniform(name, (void*)&ccc, type, true, stm);
					}
				}
			}
			ss[0] << "\n";
			ss[1] << "\n";
			ss[2] << "\n";

		}

		if (!hasShader[0]) {
			std::cout << "Reading error: No vertex shader declared!" << std::endl;
			return false;
		}
		if (!hasShader[1]) {
			std::cout << "Reading error: No fragment shader declared!" << std::endl;
			return false;
		}

		vertex = finalizeShaderText(ss[0].str(), version);
		fragment = finalizeShaderText(ss[1].str(), version);
		if(hasShader[2])
			geometry = finalizeShaderText(ss[2].str(), version);

		stream.close();
		return true;
	}

	std::string ShaderProgram::finalizeShaderText(std::string source, const std::string& version) {
		std::string allUniforms = "uniform mat4 modelMatrix; uniform mat4 viewMatrix;";
		source.insert(1, allUniforms);
		return version + source;
	}


	void ShaderProgram::createProgram(const std::string& vertexSource, const std::string& fragmentSource, const std::string& geometrySource, ShaderProgram& stm) {
		unsigned int vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER, "vertex shader");
		unsigned int fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER, "fragment shader");
		unsigned int geometryShader = (geometrySource == "") ? 1 : compileShader(geometrySource, GL_GEOMETRY_SHADER, "geometry shader");

		if (vertexShader * fragmentShader * geometryShader == 0) {
			stm.status = ShaderProgramStatus::COMPILE_ERROR;
			return;
		}
	

		stm.glId = glCreateProgram();

		glAttachShader(stm.glId, vertexShader);
		glAttachShader(stm.glId, fragmentShader);
		if(geometrySource != "")
			glAttachShader(stm.glId, geometryShader);

		glLinkProgram(stm.glId);
		glValidateProgram(stm.glId);

		if (checkForLinkingError(stm))
			return;

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		if (geometrySource != "")
			glDeleteShader(geometryShader);
	}

	bool ShaderProgram::checkForLinkingError(ShaderProgram& stm) {
		int result;
		glGetProgramiv(stm.glId, GL_LINK_STATUS, &result);
		if (result == GL_FALSE) {
			int length;
			glGetShaderiv(stm.glId, GL_INFO_LOG_LENGTH, &length);

			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(stm.glId, length, &length, message);

			std::cerr << "Linking error: " << message << std::endl;

			glDeleteShader(stm.glId);
			return true;
		}
		return false;
	}

	unsigned int ShaderProgram::compileShader(const std::string& source, unsigned int type, const std::string & name) {
		const char* sourcePtr = source.c_str();

		unsigned int shader = glCreateShader(type);
		glShaderSource(shader, 1, &sourcePtr, nullptr);

		glCompileShader(shader);

		int result;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			int length;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(shader, length, &length, message);

			std::cerr << "Compiling error in " << name << ": " << message << std::endl;

			glDeleteShader(shader);
			return 0;
		}

		return shader;
	}

	

	void ShaderProgram::prepareUniform(const std::string name, void* value, const UniformType& type, bool isDefault, ShaderProgram& stm) {
		stm.uniforms.insert({ name, {-1, isDefault, {type, Utility::punnData<UniformData::DataStorage>(value) } } });
	}

	void ShaderProgram::addAllUniforms(ShaderProgram& stm) {
		for (auto& entry : stm.uniforms) {
			int location = glGetUniformLocation(stm.glId, entry.first.c_str());
			if (location == -1 && entry.second.needsMaterial) {
				std::cout << "Warning: Uniform variable '" << entry.first << "' is not in use (" << glGetError() << ")" << std::endl;
				continue;
			}
			entry.second.location = location;
		}
	}

	#define UNIFORM_CHECK int location = uniforms.at(name).location; if(location == -1) return

	void ShaderProgram::loadBool(const std::string& name, const bool& value) const {
		UNIFORM_CHECK;
		glUniform1i(location, value ? 1 : 0);
	}
	void ShaderProgram::loadFloat(const std::string& name, const float& value) const {
		UNIFORM_CHECK;
		glUniform1f(location, value);
	}
	void ShaderProgram::loadDouble(const std::string& name, const double& value) const {
		UNIFORM_CHECK;
		glUniform1d(location, value);
	}
	void ShaderProgram::loadInt(const std::string& name, const int& value) const {
		UNIFORM_CHECK;
		glUniform1i(location, value);
	}
	void ShaderProgram::loadUInt(const std::string& name, const unsigned int& value) const {
		UNIFORM_CHECK;
		glUniform1ui(location, value);
	}
	void ShaderProgram::loadVec2(const std::string& name, const Vector2& value) const {
		UNIFORM_CHECK;
		glUniform2f(location, value[0], value[1]);
	}
	void ShaderProgram::loadVec3(const std::string& name, const Vector3& value) const {
		UNIFORM_CHECK;
		glUniform3f(location, value[0], value[1], value[2]);
	}
	void ShaderProgram::loadVec4(const std::string& name, const Vector4& value) const {
		UNIFORM_CHECK;
		glUniform4f(location, value[0], value[1], value[2], value[3]);
	}
	void ShaderProgram::loadColor(const std::string& name, const Color& value) const {
		UNIFORM_CHECK;
		glUniform4f(location, value.getR(), value.getG(), value.getB(), value.getA());
	}
	void ShaderProgram::loadMat2(const std::string& name, const Matrix2& value) const {
		UNIFORM_CHECK;
		glUniformMatrix2fv(location, 1, GL_FALSE, value.toPtr());
	}
	void ShaderProgram::loadMat3(const std::string& name, const Matrix3& value) const {
		UNIFORM_CHECK;
		glUniformMatrix3fv(location, 1, GL_FALSE, value.toPtr());
	}
	void ShaderProgram::loadMat4(const std::string& name, const Matrix4& value) const {
		UNIFORM_CHECK;
		glUniformMatrix4fv(location, 1, GL_FALSE, value.toPtr());
	}
	void ShaderProgram::loadTexture(const std::string& name, const Texture& value) const {
		UNIFORM_CHECK;
		value.bind(loadedTextures.size());
		glUniform1i(location, loadedTextures.size());
		loadedTextures.push_back(&value);
	}

	#undef UNIFORM_CHECK

	void ShaderProgram::loadUniform(const std::string& name, UniformData::DataStorage value, const UniformType& type) const {
		switch (type) {
			case UniformType::BOOL:		loadBool(name, value.boolean); break;
			case UniformType::FLOAT:	loadFloat(name, value.float32); break;
			case UniformType::DOUBLE:	loadDouble(name, value.float64); break;
			case UniformType::INT:		loadInt(name, value.integer); break;
			case UniformType::UINT:		loadUInt(name, value.uInteger); break;
			case UniformType::VEC2:		loadVec2(name, value.vector2); break;
			case UniformType::VEC3:		loadVec3(name, value.vector3); break;
			case UniformType::VEC4:		loadVec4(name, value.vector4); break;
			case UniformType::COLOR:	loadColor(name, value.color); break;
			case UniformType::MAT2:		loadMat2(name, value.matrix2); break;
			case UniformType::MAT3:		loadMat3(name, value.matrix3); break;
			case UniformType::MAT4:		loadMat4(name, value.matrix4); break;
			case UniformType::TEXTURE:	loadTexture(name, value.texture); break;
		}


	}

	void ShaderProgram::start() const {
		glUseProgram(glId);
		status = ShaderProgramStatus::RUNNING;
	}

	void ShaderProgram::stop() const {
		glUseProgram(0);
		for (const Texture* tex : loadedTextures)
			tex->unbind();
		loadedTextures.clear();
		status = ShaderProgramStatus::IDLE;
	}

	

}