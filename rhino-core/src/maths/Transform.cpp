#include "Transform.h"
#include <iostream>

namespace rhino {
	Transform::Transform() 
		:position({0.0f, 0.0f, 0.0f}), rotation(Quaternion::identity()), scale({ 1.0f, 1.0f, 1.0f }) {
	}	

	Transform::Transform(const Vector3& position)
		: position(position), rotation(Quaternion::identity()), scale({ 1.0f, 1.0f, 1.0f }) {
	}

	Transform::Transform(const Vector3& position, const Quaternion& rotation, const Vector3& scale)
		:position(position), rotation(rotation), scale(scale) {
	}

	Transform::Transform(const Vector3& position, const Quaternion& rotation, const float& scale)
		:position(position), rotation(rotation), scale({ scale, scale, scale }) {
	}

	Vector3 Transform::transform(const Vector3& v) const {
		Vector4 stm = toMatrix() * Vector4({ v[0], v[1], v[2], 1.0f });
		return Vector3({ stm[0], stm[1], stm[2] });
	}


	Matrix4 Transform::toMatrix(const TransformScope& scope) const {
		return MatrixFactory::modelMatrix(position, rotation, scale);
	}

	void Transform::translate(const Vector3& translation, const TransformScope& scope) {
		switch (scope) {
			case TransformScope::GLOBAL: position += translation; break;
			case TransformScope::LOCAL: position += rotation.rotate(translation); break;
		}
	}

	void Transform::rotate(const Quaternion& rot) {
		rotation *= rot;
	}


	std::string Transform::toString() const {
		return "Trfm[" + position.toString() + ", " + rotation.toString() + ", " + scale.toString() + "]";
	}

}

