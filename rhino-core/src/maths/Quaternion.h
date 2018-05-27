#pragma once

#include "Vector.h"

namespace rhino {
	class Quaternion : public IPrintable {

		private:
			float x, y, z, w;
		
		public:
			Quaternion(float x, float y, float z, float w);
			static Quaternion axisAngle(Vector3 axis, float angle);
			static Quaternion eulerAngles(const Vector3& euler);

			float operator[](const unsigned int& i) const;
			float& operator[](const unsigned int& i);

			inline float getX() const { return x; }
			inline float getY() const { return y; }
			inline float getZ() const { return z; }
			inline float getW() const { return w; }

			Quaternion operator*(const Quaternion& q) const;
			Quaternion& operator*=(const Quaternion& q);
			Quaternion operator*(const Vector3& v) const;
			Quaternion& operator*=(const Vector3& v);

			Quaternion& operator=(const Quaternion& q);
			
			bool operator==(const Quaternion& q) const;

			Vector3 rotate(const Vector3& v) const;

			float magnitudeSqr() const;
			float magnitude() const;

			Quaternion& normalize();
			Quaternion normalized() const;

			Quaternion conjugate() const;

			std::string toString() const;
			Vector3 toEulerAngles() const;

			Vector3 forward() const;
			Vector3 up() const;
			Vector3 right() const;

			static Quaternion identity();
	};

}
