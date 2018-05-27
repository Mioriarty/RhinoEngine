#pragma once

#include "Matrix.h"
#include "Vector.h"
#include "Quaternion.h"

namespace rhino {

	struct MatrixFactory {

		static Matrix4 translationMatrix(const Vector3& pos) {
			Matrix4 m = Matrix4::identity();
			m(0, 3) = pos[0];
			m(1, 3) = pos[1];
			m(2, 3) = pos[2];
			return m;
		}

		static Matrix4 scaleMatrix(const Vector3& scale) {
			Matrix4 m;
			m(0, 0) = scale[0];
			m(1, 1) = scale[1];
			m(2, 2) = scale[2];
			m(3, 3) = 1.0f;
			return m;
		}

		static Matrix4 rotationMatrix(const Quaternion& rotation) {
			Quaternion q = rotation.normalized().conjugate();

			Matrix4 m1 = {
				q.getW(), q.getZ(), -q.getY(), q.getX(),
				-q.getZ(), q.getW(), q.getX(), q.getY(),
				q.getY(), -q.getX(), q.getW(), q.getZ(),
				-q.getX(), -q.getY(), -q.getZ(), q.getW()
			};

			Matrix4 m2 = {
				q.getW(), q.getZ(), -q.getY(), -q.getX(),
				-q.getZ(), q.getW(), q.getX(), -q.getY(),
				q.getY(), -q.getX(), q.getW(), -q.getZ(),
				q.getX(), q.getY(), q.getZ(), q.getW()
			};

			return m1 * m2;
		}

		static Matrix4 modelMatrix(const Vector3& position, const Quaternion& rotation, const Vector3& scale) {
			return translationMatrix(position) * rotationMatrix(rotation) * scaleMatrix(scale);
		}

		static Matrix4 viewMatrix(const Vector3& camPos, const Quaternion& camRot) {
			return rotationMatrix(camRot.conjugate()) * translationMatrix(camPos * -1.0f);
		}

		static Matrix4 perspectiveProjectionMatrix(float fov, float nearPlane, float farPlane, float aspectRatio) {
			float tanFovHalf = tan(fov * 0.5f / 180.0f * 3.1415926535897f);
			float frustumLength = farPlane - nearPlane;

			Matrix4 stm;
			stm(0, 0) = 1.0f / tanFovHalf / aspectRatio;
			stm(1, 1) = 1.0f / tanFovHalf;
			stm(2, 2) = -((farPlane + nearPlane) / frustumLength);
			stm(2, 3) = -(2.0f * farPlane * nearPlane / frustumLength);
			stm(3, 2) = -1.0f;

			return stm;
		}

		static Matrix4 orthographicProjectionMatrix(float orthographicSie, float nearPlane, float farPlane, float aspectRatio) {
			return Matrix4::identity();
		}
	};
}