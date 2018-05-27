#pragma once

#include "maths\maths.h"
#include "../Texture.h"

namespace rhino {

	enum class UniformType {
		BOOL, FLOAT, DOUBLE, INT, UINT, VEC2, VEC3, VEC4, COLOR, MAT2, MAT3, MAT4, TEXTURE,
		ERROR

	};


	struct UniformData {
		UniformType type;

		union DataStorage {
			bool boolean;
			float float32;
			double float64;
			int integer;
			unsigned int uInteger;
			Vector2 vector2;
			Vector3 vector3;
			Vector4 vector4;
			Color color;
			Matrix2 matrix2;
			Matrix3 matrix3;
			Matrix4 matrix4;
			Texture texture;

			DataStorage() {
				memset(this, 0, sizeof(DataStorage));
			}

			DataStorage(const DataStorage& other) {
				memcpy(this, &other, sizeof(DataStorage));
			}

			void operator=(const DataStorage& other) {
				memcpy(this, &other, sizeof(DataStorage));
			}

			~DataStorage() {};

		} value;
	};

	inline unsigned int uniformTypeToSize(const UniformType& type) {
		switch (type) {
			case UniformType::BOOL: return sizeof(bool);
			case UniformType::FLOAT: return sizeof(float);
			case UniformType::DOUBLE: return sizeof(double);
			case UniformType::INT: return sizeof(int);
			case UniformType::UINT: return sizeof(unsigned int);
			case UniformType::VEC2: return sizeof(Vector2);
			case UniformType::VEC3: return sizeof(Vector3);
			case UniformType::VEC4: return sizeof(Vector4);
			case UniformType::COLOR: return sizeof(Color);
			case UniformType::MAT2: return sizeof(Matrix2);
			case UniformType::MAT3: return sizeof(Matrix3);
			case UniformType::MAT4: return sizeof(Matrix4);
			case UniformType::TEXTURE: return sizeof(Texture);
			default: return 0;
		}
	}

	template<typename T>
	inline bool checkType(const UniformType& type) {
		switch (type) {
			case UniformType::BOOL: return typeid(T) == typeid(bool);
			case UniformType::FLOAT: return typeid(T) == typeid(float);
			case UniformType::DOUBLE: return typeid(T) == typeid(double);
			case UniformType::INT: return typeid(T) == typeid(int);
			case UniformType::UINT: return typeid(T) == typeid(unsigned int);
			case UniformType::VEC2: return typeid(T) == typeid(Vector2);
			case UniformType::VEC3: return typeid(T) == typeid(Vector3);
			case UniformType::VEC4: return typeid(T) == typeid(Vector4);
			case UniformType::COLOR: return typeid(T) == typeid(Color);
			case UniformType::MAT2: return typeid(T) == typeid(Matrix2);
			case UniformType::MAT3: return typeid(T) == typeid(Matrix3);
			case UniformType::MAT4: return typeid(T) == typeid(Matrix4);
			case UniformType::TEXTURE: return typeid(T) == typeid(Texture);
			default: return false;
		}
	}

	inline UniformType stringToUniformType(const std::string& str) {
		if(str == "bool")	return UniformType::BOOL;
		if(str == "float")	return UniformType::FLOAT;
		if(str == "double") return UniformType::DOUBLE; 
		if(str == "int")	return UniformType::INT;
		if(str == "uint")	return UniformType::UINT; 
		if(str == "vec2")	return UniformType::VEC2;
		if(str == "vec3")	return UniformType::VEC3;
		if(str == "vec4")	return UniformType::VEC4;
		if(str == "color")	return UniformType::COLOR;
		if(str == "mat2")	return UniformType::MAT2; 
		if(str == "mat3")	return UniformType::MAT3; 
		if(str == "mat4")	return UniformType::MAT4; 
		if(str == "sampler2D")return UniformType::TEXTURE;
		return UniformType::ERROR;
	}

	inline std::string uniformTypeToString(const UniformType& type) {
		switch (type) {
			case UniformType::BOOL:		return "bool";
			case UniformType::FLOAT:	return "float";
			case UniformType::DOUBLE:	return "double";
			case UniformType::INT:		return "int";
			case UniformType::UINT:		return "uint";
			case UniformType::VEC2:		return "vec2";
			case UniformType::VEC3:		return "vec3";
			case UniformType::VEC4:		return "vec4";
			case UniformType::COLOR:	return "vec4";
			case UniformType::MAT2:		return "mat2";
			case UniformType::MAT3:		return "mat3";
			case UniformType::MAT4:		return "mat4";
			case UniformType::TEXTURE:	return "sampler2D";
			default: return "";
		}
	}


}