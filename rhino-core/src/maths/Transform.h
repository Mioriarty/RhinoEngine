#pragma once

#include "MatrixFactory.h"

namespace rhino {

	enum class TransformScope {
		GLOBAL, LOCAL
	};


	class Transform : public IPrintable {

		private:
			Vector3 position, scale;
			Quaternion rotation;

		public:
			Transform();
			Transform(const Vector3& position);
			Transform(const Vector3& position, const Quaternion& rotation, const Vector3& scale = {1.0f, 1.0f, 1.0f});
			Transform(const Vector3& position, const Quaternion& rotation, const float& scale);

			Vector3 transform(const Vector3& v) const;

			Matrix4 toMatrix(const TransformScope& scope = TransformScope::GLOBAL) const;

			void translate(const Vector3& translation, const TransformScope& scope = TransformScope::GLOBAL);
			void rotate(const Quaternion& rot);

			std::string toString() const;

			inline const Vector3& getPosition() const { return position; };
			inline const Quaternion& getRotation() const { return rotation; };
			inline const Vector3& getScale() const { return scale; };

			inline void setPosition(const Vector3& v) { position = v; };
			inline void setRotation(const Quaternion& v) { rotation = v; };
			inline void setScale(const Vector3& v) { scale = v; };
	};


}

