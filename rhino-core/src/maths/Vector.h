#pragma once

#include "../utility/interfaces/IPrintable.h"

#include <string>
#include <cstdarg>
#include <cmath>
#include <ostream>

namespace rhino {

	template<unsigned int L, typename T>
	class Vector : public IPrintable {

		private:
			T values[L];

		public:
			Vector();
			Vector(std::initializer_list<T> list);
			Vector(T f, ...);
			
			
			template<unsigned int O, typename P>
			Vector(const Vector<O, P>& other);

			const T* toPtr() const;
			
			const T& operator[](const unsigned int& index) const;
			T& operator[](const unsigned int& index);

			Vector<L, T> operator+(const Vector<L, T>& v) const;
			Vector<L, T>& operator+=(const Vector<L, T>& v);

			Vector<L, T> operator-(const Vector<L, T>& v) const;
			Vector<L, T>& operator-=(const Vector<L, T>& v);

			Vector<L, T> operator*(const T& f) const;
			Vector<L, T>& operator*=(const T& f);

			Vector<L, T> operator/(const T& f) const;
			Vector<L, T>& operator/=(const T& f);

			Vector<L, T>& operator=(const Vector<L, T>& v);

			template<unsigned int O, typename P>
			bool operator==(const Vector<O, P>& v) const;

			std::string toString() const override;

			float magnitudeSqr() const;
			float magnitude() const;

			Vector<L, T>& normalize();
			Vector<L, T> normalized() const;

			template<typename P>
			Vector<L, T> cross(const Vector<L, P>& other) const;
			template<typename P>
			T dot(const Vector<L, P>& other) const;

			template<typename P>
			static T distance(const Vector<L, T>& v1, const Vector<L, P>& v2);
			static Vector<L, T> lerp(const Vector<L, T>& v1, const Vector<L, T>& v2, float value);
			static T angle(const Vector<L, T>& v1, const Vector<L, T>& v2);
			static Vector<L, T> clampMagnitude(const Vector<L, T>& v, float maxMagnitude);
			static Vector<L, T> reflect(const Vector<L, T>& v, const Vector<L, T>& normal);

			static Vector<L, T> zero();
			static Vector<L, T> up();
			static Vector<L, T> down();
			static Vector<L, T> left();
			static Vector<L, T> right();
			static Vector<L, T> forward();
			static Vector<L, T> backward();

	};


	typedef Vector<2, float> Vector2f;
	typedef Vector<3, float> Vector3f;
	typedef Vector<4, float> Vector4f;

	typedef Vector<2, int> Vector2i;
	typedef Vector<3, int> Vector3i;
	typedef Vector<4, int> Vector4i;

	typedef Vector<2, unsigned int> Vector2u;
	typedef Vector<3, unsigned int> Vector3u;
	typedef Vector<4, unsigned int> Vector4u;

	typedef Vector<2, double> Vector2d;
	typedef Vector<3, double> Vector3d;
	typedef Vector<4, double> Vector4d;

	typedef Vector2f Vector2;
	typedef Vector3f Vector3;
	typedef Vector4f Vector4;


	//////////////////
	//IMPLEMENTATION//
	//////////////////


	template<unsigned int L, typename T>
	inline Vector<L, T>::Vector() {
		for (int i = 0; i <L; i++)
			values[i] = 0.0f;
	}

	template<unsigned int L, typename T>
	inline Vector<L, T>::Vector(std::initializer_list<T> list) {
		int c = 0;
		for (T f : list)
			values[c++] = f;
	}

	template<unsigned int L, typename T>
	inline Vector<L, T>::Vector(T f, ...) {
		values[0] = f;
		va_list args;
		va_start(args, f);
		for (int i = 1; i <L; i++) {
			double d = va_arg(args, double);
			values[i] = T(d);
		}
		va_end(args);
	}

	template<unsigned int L, typename T>
	template<unsigned int O, typename P>
	inline Vector<L, T>::Vector(const Vector<O, P>& other) {
		for (int i = 0; i <L; i++)
			if (i < O)
				values[i] = T(other[i]);
			else
				values[i] = T(0);
	}

	template<unsigned int L, typename T>
	inline const T* Vector<L, T>::toPtr() const {
		return values;
	}

	template<unsigned int L, typename T>
	inline const T& Vector<L, T>::operator[](const unsigned int& index) const {
		return values[index];
	}

	template<unsigned int L, typename T>
	inline T& Vector<L, T>::operator[](const unsigned int& index) {
		return values[index];
	}


	template<unsigned int L, typename T>
	inline Vector<L, T> Vector<L, T>::operator+(const Vector<L, T>& v) const {
		Vector<L, T> stm;
		for (unsigned int i = 0; i <L; i++)
			stm[i] = values[i] + v[i];
		return stm;
	}

	template<unsigned int L, typename T>
	inline Vector<L, T>& Vector<L, T>::operator+=(const Vector<L, T>& v) {
		*this = *this + v;
		return *this;
	}


	template<unsigned int L, typename T>
	inline Vector<L, T> Vector<L, T>::operator-(const Vector<L, T>& v) const {
		Vector<L, T> stm;
		for (unsigned int i = 0; i <L; i++)
			stm[i] = values[i] - v[i];
		return stm;
	}

	template<unsigned int L, typename T>
	inline Vector<L, T>& Vector<L, T>::operator-=(const Vector<L, T>& v) {
		*this = *this - v;
		return *this;
	}


	template<unsigned int L, typename T>
	inline Vector<L, T> Vector<L, T>::operator*(const T& f) const {
		Vector<L, T> stm;
		for (unsigned int i = 0; i <L; i++)
			stm[i] = f * values[i];
		return stm;
	}

	template<unsigned int L, typename T>
	inline Vector<L, T>& Vector<L, T>::operator*=(const T& f) {
		*this = *this * f;
		return *this;
	}


	template<unsigned int L, typename T>
	inline Vector<L, T> Vector<L, T>::operator/(const T& f) const {
		Vector<L, T> stm;
		for (unsigned int i = 0; i <L; i++)
			stm[i] = values[i] / f;
		return stm;
	}

	template<unsigned int L, typename T>
	inline Vector<L, T>& Vector<L, T>::operator/=(const T& f) {
		*this = *this / f;
		return *this;
	}


	template<unsigned int L, typename T>
	inline Vector<L, T>& Vector<L, T>::operator=(const Vector<L, T>& v) {
		for (unsigned int i = 0; i <L; i++)
			values[i] = v[i];
		return *this;
	}


	template<unsigned int L, typename T>
	template<unsigned int O, typename P>
	inline bool Vector<L, T>::operator==(const Vector<O, P>& v) const {
		if (L != O)
			return false;
		for (int i = 0; i <L; i++)
			if (values[i] != v[i])
				return false;
		return true;
	}

	template<unsigned int L, typename T>
	inline std::string Vector<L, T>::toString() const {
		std::string stm = "Vec" + std::to_string(L) + "[" + std::to_string(values[0]);
		for (int i = 1; i <L; i++)
			stm += ", " + std::to_string(values[i]);
		return stm + "]";
	}





	template<unsigned int L, typename T>
	inline float Vector<L, T>::magnitudeSqr() const {
		float stm = 0;
		for (int i = 0; i <L; i++)
			stm += float(values[i] * values[i]);
		return stm;
	}

	template<unsigned int L, typename T>
	inline float Vector<L, T>::magnitude() const {
		return sqrtf(magnitudeSqr());
	}

	template<unsigned int L, typename T>
	inline Vector<L, T>& Vector<L, T>::normalize() {
		*this /= magnitude();
		return *this;
	}

	template<unsigned int L, typename T>
	inline Vector<L, T> Vector<L, T>::normalized() const {
		return *this / magnitude();
	}

	template<unsigned int L, typename T>
	template<typename P>
	inline Vector<L, T> Vector<L, T>::cross(const Vector<L, P>& other) const {
		Vector<L, T> stm;
		int i1, i2;
		for (int i = 0; i <L; i++) {
			i1 = (i + 1) % L;
			i2 = (i + 2) % L;
			stm[i] = values[i1] * other[i2] - values[i2] * other[i1];
		}
		return stm;
	}

	template<unsigned int L, typename T>
	template<typename P>
	inline T Vector<L, T>::dot(const Vector<L, P>& other) const {
		T stm = 0;
		for (int i = 0; i <L; i++)
			stm += values[i] * other[i];
		return stm;
	}


	template<unsigned int L, typename T>
	template<typename P>
	static T Vector<L, T>::distance(const Vector<L, T>& v1, const Vector<L, P>& v2) {
		return (v1 - v2).magnitude();
	}

	template<unsigned int L, typename T>
	static Vector<L, T> Vector<L, T>::lerp(const Vector<L, T>& v1, const Vector<L, T>& v2, float value) {
		return (v2 - v1) * value + v1;
	}

	template<unsigned int L, typename T>
	static T Vector<L, T>::angle(const Vector<L, T>& v1, const Vector<L, T>& v2) {
		return acosf(v1.dot(v2) / (v1.magnitude() * v2.magnitude())); 
	}

	template<unsigned int L, typename T>
	static Vector<L, T> Vector<L, T>::clampMagnitude(const Vector<L, T>& v, float maxMagnitude) {
		return v.magnitudeSqr() > maxMagnitude * maxMagnitude ? maxMagnitude / v.magnitude() * v : v;
	}

	template<unsigned int L, typename T>
	Vector<L, T> Vector<L, T>::reflect(const Vector<L, T>& v, const Vector<L, T>& normal) {
		return normal.normalized() * 2.0f * v.dot(normal.normalized()) - v;
	}

	template<unsigned int L, typename T>
	inline Vector<L, T> Vector<L, T>::zero() {
		return Vector<L, T>();
	}
	template<unsigned int L, typename T>
	inline Vector<L, T> Vector<L, T>::up() {
		Vector<L, T> stm;
		stm[1] = T(1);
		return stm;
	}
	template<unsigned int L, typename T>
	inline Vector<L, T> Vector<L, T>::down() {
		Vector<L, T> stm;
		stm[1] = T(-1);
		return stm;
	}
	template<unsigned int L, typename T>
	inline Vector<L, T> Vector<L, T>::left() {
		Vector<L, T> stm;
		stm[0] = T(-1);
		return stm;
	}
	template<unsigned int L, typename T>
	inline Vector<L, T> Vector<L, T>::right() {
		Vector<L, T> stm;
		stm[0] = T(1);
		return stm;
	}
	template<unsigned int L, typename T>
	inline Vector<L, T> Vector<L, T>::forward() {
		Vector<L, T> stm;
		stm[2] = T(1);
		return stm;
	}
	template<unsigned int L, typename T>
	inline Vector<L, T> Vector<L, T>::backward() {
		Vector<L, T> stm;
		stm[2] = T(-1);
		return stm;
	}


/*	template<unsigned int L, typename T> inline Vector<2, T> Vector<2, T>::up()		{ return { T(1),  T(0) }; }
	template<unsigned int L, typename T> inline Vector<2, T> Vector<2, T>::down()		{ return { T(-1), T(0) }; }
	template<unsigned int L, typename T> inline Vector<2, T> Vector<2, T>::left()		{ return { T(0),  T(-1) }; }
	template<unsigned int L, typename T> inline Vector<2, T> Vector<2, T>::right()	{ return { T(0),  T(1) }; }
	template<unsigned int L, typename T> inline Vector<2, T> Vector<2, T>::forward()	{ return { T(0),  T(0) }; }
	template<unsigned int L, typename T> inline Vector<2, T> Vector<2, T>::backward()	{ return { T(0),  T(0) }; }*/

}


