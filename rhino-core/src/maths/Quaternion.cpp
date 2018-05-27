#include "Quaternion.h"

#include <iostream>

#define TORAD(x)  (x) / 180.0f * 3.1415926535897f
#define TOGRAD(x) (x) * 180.0f / 3.1415926535897f
namespace rhino {

	Quaternion::Quaternion(float x, float y, float z, float w) 
		:x(x), y(y), z(z), w(w){
	}

	Quaternion Quaternion::axisAngle(Vector3 axis, float angle) {
		float sinHalf = sinf(TORAD(angle) * 0.5f);
		float cosHalf = cosf(TORAD(angle) * 0.5f);
		axis.normalize();

		float x = axis[0] * sinHalf;
		float y = axis[1] * sinHalf;
		float z = axis[2] * sinHalf;
		float w = cosHalf;
		return Quaternion(x, y, z, w);
	}

	Quaternion Quaternion::eulerAngles(const Vector3& euler) {
		float c1 = cosf(TORAD(euler[0] / 2.0f));
		float c2 = cosf(TORAD(euler[1] / 2.0f));
		float c3 = cosf(TORAD(euler[2] / 2.0f));
		float s1 = sinf(TORAD(euler[0] / 2.0f));
		float s2 = sinf(TORAD(euler[1] / 2.0f));
		float s3 = sinf(TORAD(euler[2] / 2.0f));
		float x = s1 * c2 * c3 + c1 * s2 * s3;
		float y = c1 * s2 * c3 - s1 * c2 * s3;
		float z = c1 * c2 * s3 + s1 * s2 * c3;
		float w = c1 * c2 * c3 - s1 * s2 * s3;

		return Quaternion(x, y, z, w);
	}


	float Quaternion::operator[](const unsigned int& i) const {
		switch (i) {
			case 0: return x;
			case 1: return y;
			case 2: return z;
			case 3: return w;
			default: return 0.0f;
		}
	}

	float& Quaternion::operator[](const unsigned int& i) {
		switch (i) {
			case 0: return x;
			case 1: return y;
			case 2: return z;
			case 3: return w;
			default: return x;
		}
	}



	Quaternion Quaternion::operator*(const Quaternion& q) const {
		float w_ = w * q.getW() - x * q.getX() - y * q.getY() - z * q.getZ();
		float x_ = x * q.getW() + w * q.getX() + y * q.getZ() - z * q.getY();
		float y_ = y * q.getW() + w * q.getY() + z * q.getX() - x * q.getZ();
		float z_ = z * q.getW() + w * q.getZ() + x * q.getY() - y * q.getX();
		return Quaternion(x_, y_, z_, w_);
	}

	Quaternion& Quaternion::operator*=(const Quaternion& q) {
		*this = *this * q;
		return *this;
	}

	Quaternion Quaternion::operator*(const Vector3& v) const {
		return *this * Quaternion(v[0], v[1], v[2], 0.0f);
	}

	Quaternion& Quaternion::operator*=(const Vector3& v) {
		*this = *this * v;
		return *this;
	}

	Quaternion& Quaternion::operator=(const Quaternion& q) {
		x = q.getX();
		y = q.getY();
		z = q.getZ();
		w = q.getW();
		return *this;
	}

	bool Quaternion::operator==(const Quaternion& q) const {
		if (x != q.getX())
			return false;
		if (y != q.getY())
			return false;
		if (z != q.getZ())
			return false;
		if (w != q.getW())
			return false;
		return true;
	}

	float Quaternion::magnitudeSqr() const {
		return x * x + y * y + z * z + w * w;
	}

	float Quaternion::magnitude() const {
		return sqrtf(magnitudeSqr());
	}

	Quaternion& Quaternion::normalize() {
		float magn = magnitude();
		x /= magn;
		y /= magn;
		z /= magn;
		w /= magn;
		return *this;
	}

	Quaternion Quaternion::normalized() const {
		float magn = magnitude();
		return Quaternion(x / magn, y / magn, z / magn, w / magn);
	}


	Vector3 Quaternion::rotate(const Vector3& v) const {
		Quaternion w = (*this * v) * conjugate();
		return Vector3(w.getX(), w.getY(), w.getZ());
	}


	Quaternion Quaternion::conjugate() const {
		return Quaternion(-x, -y, -z, w);
	}

	Quaternion Quaternion::identity() {
		return Quaternion(0.0f, 0.0f, 0.0f, 1.0f); 
	}

	std::string Quaternion::toString() const {
		return "Qtn[" + std::to_string(x) + "i, " + std::to_string(y) + "j, " + std::to_string(z) + "k, " + std::to_string(w) + "]";
	}

	Vector3 Quaternion::toEulerAngles() const {
		float r11 = 2 * (x*y + w*z);
		float r12 = w*w + x*x - y*y - z*z;
		float r21 = -2 * (x*z - w*y);
		float r31 = 2 * (y*z + w*x);
		float r32 = w*w - x*x - y*y + z*z;

		return Vector3({TOGRAD(atan2(r31, r32)), TOGRAD(asin(r21)), TOGRAD(atan2(r11, r12)) });
	}

	Vector3 Quaternion::forward() const {
		return this->rotate(Vector3::forward());
	}

	Vector3 Quaternion::up() const {
		return this->rotate(Vector3::up());
	}

	Vector3 Quaternion::right() const {
		return this->rotate(Vector3::right());
	}

}

