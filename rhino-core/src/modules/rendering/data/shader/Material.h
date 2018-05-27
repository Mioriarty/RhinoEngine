#pragma once

#include "ShaderProgram.h"

namespace rhino {

	class Material {

		private:
			std::unordered_map<std::string, UniformData> values;
			const ShaderProgram* referenceShader;


		public:
			Material(ShaderProgram*& shader);
			~Material();

			template<typename T>
			void setProperty(const std::string& name, const T& value);

			void loadAll() const;

			inline const std::unordered_map<std::string, UniformData>& getValues() const { return values; }
			inline const ShaderProgram* getReferceShader() const { return referenceShader; };

	};


	template<typename T>
	inline void Material::setProperty(const std::string& name, const T& value) {
		if (!values.count(name)) {
			std::cout << "Material access error: Tried to access undefined property (" << name << ")" << std::endl;
			return;
		}
		if (!checkType<T>(values[name].type)) {
			std::cout << "Material access error: Property type and value type do not match (" << name << ": " << typeid(T).name() << ")" << std::endl;
			return;
		}
		values[name].value = Utility::punnData<UniformData::DataStorage, T>(value);
		
	}
}