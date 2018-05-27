#pragma once

#include <string>
#include <cmath>
#include <iostream>
#include "Vector.h"

#define GET(y, x) (x) * H + (y)

namespace rhino {
	
	template<unsigned int H, unsigned int W, typename T>
	class Matrix : public IPrintable {

		private:
			T values[H * W];

		public:
			Matrix();
			Matrix(std::initializer_list<T> list);

			T operator()(const unsigned int& y, const unsigned int& x) const;
			T& operator()(const unsigned int& y, const unsigned int& x);

			const T* toPtr() const;

			Matrix<H, W, T> operator+(const Matrix<H, W, T>& m) const;
			Matrix<H, W, T>& operator+=(const Matrix<H, W, T>& m);

			Matrix<H, W, T> operator-(const Matrix<H, W, T>& m) const;
			Matrix<H, W, T>& operator-=(const Matrix<H, W, T>& m);

			Matrix<H, W, T> operator*(const T& f) const;
			Matrix<H, W, T>& operator*=(const T& f);

			Matrix<H, W, T> operator/(const T& f) const;
			Matrix<H, W, T>& operator/=(const T& f);

			template<unsigned int A, unsigned int B, typename P>
			Matrix<H, B, T> operator*(const Matrix<A, B, P>& m) const;
			template<unsigned int A, unsigned int B, typename P>
			Matrix<H, B, T>& operator*=(const Matrix<A, B, P>& m);

			template<typename P>
			Vector<H, T> operator*(const Vector<W, P>& v) const;


			Matrix<H, W, T>& operator=(const Matrix<H, W, T>& m);

			template<unsigned int A, unsigned int B, typename P>
			bool operator==(const Matrix<A, B, P>& m) const;

			std::string toString() const;

			T det() const;
			T minor(unsigned int y, unsigned int x) const;
			Matrix<W, H, T> transpose() const;
			Matrix<H, W, T> inverse() const;
			Matrix<H, W, T> cof() const;
			Matrix<H, W, T> adj() const;

			static Matrix<H, W, T> identity();

	};

	typedef Matrix<4, 4, float> Matrix4f;
	typedef Matrix<3, 3, float> Matrix3f;
	typedef Matrix<2, 2, float> Matrix2f;

	typedef Matrix<4, 4, int> Matrix4i;
	typedef Matrix<3, 3, int> Matrix3i;
	typedef Matrix<2, 2, int> Matrix2i;

	typedef Matrix<4, 4, unsigned int> Matrix4u;
	typedef Matrix<3, 3, unsigned int> Matrix3u;
	typedef Matrix<2, 2, unsigned int> Matrix2u;

	typedef Matrix<4, 4, double> Matrix4d;
	typedef Matrix<3, 3, double> Matrix3d;
	typedef Matrix<2, 2, double> Matrix2d;

	typedef Matrix4f Matrix4;
	typedef Matrix3f Matrix3;
	typedef Matrix2f Matrix2;


	//////////////////
	//IMPLEMENTATION//
	//////////////////


	template<unsigned int H, unsigned int W, typename T>
	inline Matrix<H, W, T>::Matrix() {
		for (int i = 0; i < H*W; i++)
			values[i] = 0;
	}

	template<unsigned int H, unsigned int W, typename T>
	inline Matrix<H, W, T>::Matrix(std::initializer_list<T> list) {
		unsigned int c = 0;
		for (T f : list) {
			values[GET(c / W, c % W)] = f;
			c++;
		}
	}



	template<unsigned int H, unsigned int W, typename T>
	inline T Matrix<H, W, T>::operator()(const unsigned int& y, const unsigned int& x) const {
		return values[GET(y, x)];
	}

	template<unsigned int H, unsigned int W, typename T>
	inline T& Matrix<H, W, T>::operator()(const unsigned int& y, const unsigned int& x) {
		return values[GET(y, x)];
	}


	template<unsigned int H, unsigned int W, typename T>
	inline const T* Matrix<H, W, T>::toPtr() const {
		return values;
	}

	template<unsigned int H, unsigned int W, typename T>
	inline Matrix<H, W, T> Matrix<H, W, T>::operator+(const Matrix<H, W, T>& m) const {
		Matrix<H, W, T> stm;
		for (int i = 0; i < H*W; i++)
			stm.values[i] = values[i] + m.values[i];
		return stm;
	}

	template<unsigned int H, unsigned int W, typename T>
	inline Matrix<H, W, T>& Matrix<H, W, T>::operator+=(const Matrix<H, W, T>& m) {
		for (int i = 0; i < H*W; i++)
			values[i] += m.values[i];
		return *this;
	}


	template<unsigned int H, unsigned int W, typename T>
	inline Matrix<H, W, T> Matrix<H, W, T>::operator-(const Matrix<H, W, T>& m) const {
		Matrix<H, W, T> stm;
		for (int i = 0; i < H*W; i++)
			stm.values[i] = values[i] - m.values[i];
		return stm;
	}

	template<unsigned int H, unsigned int W, typename T>
	inline Matrix<H, W, T>& Matrix<H, W, T>::operator-=(const Matrix<H, W, T>& m) {
		for (int i = 0; i < H*W; i++)
			values[i] -= m.values[i];
		return *this;
	}


	template<unsigned int H, unsigned int W, typename T>
	inline Matrix<H, W, T> Matrix<H, W, T>::operator*(const T& f) const {
		Matrix<H, W, T> stm;
		for (int i = 0; i < H*W; i++)
			stm.values[i] = values[i] * f;
		return stm;
	}

	template<unsigned int H, unsigned int W, typename T>
	inline Matrix<H, W, T>& Matrix<H, W, T>::operator*=(const T& f) {
		for (int i = 0; i < H*W; i++)
			values[i] *= f;
		return *this;
	}

	template<unsigned int H, unsigned int W, typename T>
	inline Matrix<H, W, T> Matrix<H, W, T>::operator/(const T& f) const {
		Matrix<H, W, T> stm;
		for (int i = 0; i < H*W; i++)
			stm.values[i] = values[i] / f;
		return stm;
	}

	template<unsigned int H, unsigned int W, typename T>
	inline Matrix<H, W, T>& Matrix<H, W, T>::operator/=(const T& f) {
		for (int i = 0; i < H*W; i++)
			values[i] /= f;
		return *this;
	}

	template<unsigned int H, unsigned int W, typename T>
	template<unsigned int A, unsigned int B, typename P>
	inline Matrix<H, B, T> Matrix<H, W, T>::operator*(const Matrix<A, B, P>& m) const {
		Matrix<H, B, T> stm;
		for (int y1 = 0; y1 < H; y1++) {
			for (int x2 = 0; x2 < B; x2++) {
				T f = 0;
				for (int i = 0; i < W; i++) {
					f += values[GET(y1, i)] * T(m(i, x2));
				}
				stm(y1, x2) = f;
			}
		}
		return stm;
	}

	template<unsigned int H, unsigned int W, typename T>
	template<unsigned int A, unsigned int B, typename P>
	inline Matrix<H, B, T>& Matrix<H, W, T>::operator*=(const Matrix<A, B, P>& m) {
		*this = *this * m;
		return *this;
	}

	template<unsigned int H, unsigned int W, typename T>
	template<typename P>
	inline Vector<H, T> Matrix<H, W, T>::operator*(const Vector<W, P>& v) const {
		Vector<H, T> stm;
		for (int y = 0; y < H; y++) {
			T f = 0;
			for (int x = 0; x < W; x++)
				f += values[GET(y, x)] * T(v[x]);
			stm[y] = f;
		}
		return stm;
	}

	template<unsigned int H, unsigned int W, typename T>
	inline Matrix<H, W, T>& Matrix<H, W, T>::operator=(const Matrix<H, W, T>& m) {
		for (int y = 0; y < H; y++)
			for (int x = 0; x < W; x++)
				values[GET(y, x)] = m(y, x);
		return *this;
	}


	template<unsigned int H, unsigned int W, typename T>
	template<unsigned int A, unsigned int B, typename P>
	inline bool Matrix<H, W, T>::operator==(const Matrix<A, B, P>& m) const {
		if (H != A || W != B)
			return false;
		for (int y = 0; y < H; y++)
			for (int x = 0; x < W; x++)
				if (values[GET(y, x)] != T(m(y, x)))
					return false;
		return true;
	}


	template<unsigned int H, unsigned int W, typename T>
	inline T Matrix<H, W, T>::det() const {
		static_assert(H == W, "Triying to get the determinate of a matrix not being a square");

		T stm = 0.0f;
		for (int x = 0; x < W; x++) {
			T f1 = 1.0f;
			T f2 = 1.0f;

			for (int y = 0; y < H; y++) {
				f1 *= values[GET(y, (x + y) % W)];
				f2 *= values[GET(y, (x - y + W) % W)];
			}
			stm += f1 - f2;
		}
		return stm;
	}

	inline float Matrix<1, 1, float>::det() const {
		return values[0];
	}

	inline float Matrix<2, 2, float>::det() const {
		return values[0] * values[3] - values[1] * values[2];
	}

	template<unsigned int H, unsigned int W, typename T>
	inline T Matrix<H, W, T>::minor(unsigned int row, unsigned int column) const {
		static_assert(W == H, "Triying to get the minor of a matrix not being a square");
		Matrix<H - 1, W - 1> minorMat;
		for (unsigned int y = 0; y < H-1; y++) {
			for (unsigned int x = 0; x < W-1; x++) {
				minorMat(y, x) = values[GET(y >= row ? y+1 : y, x >= column ? x+1 : x)];
			}
		}
		return minorMat.det();
	}



	template<unsigned int H, unsigned int W, typename T>
	inline std::string Matrix<H, W, T>::toString() const {
		std::string stm = "Mat";
		if (H == W)
			stm += std::to_string(H) + "[";
		else
			stm += std::to_string(H) + "x" + std::to_string(W) + "[";

		for (int y = 0; y < H; y++) {
			stm += "(";
			for (int x = 0; x < W; x++) {
				stm += std::to_string(values[GET(y, x)]);
				if (x < W - 1)
					stm += ", ";
			}

			stm += ")";
			if (y < H - 1)
				stm += ", ";
		}

		return stm + "]";
	}

	template<unsigned int H, unsigned int W, typename T>
	inline Matrix<W, H, T> Matrix<H, W, T>::transpose() const {
		Matrix<W, H, T> stm;
		for (int y = 0; y < H; y++)
			for (int x = 0; x < W; x++)
				stm(x, y) = values[GET(y, x)];
		return stm;

	}

	template<unsigned int H, unsigned int W, typename T>
	inline Matrix<H, W, T> Matrix<H, W, T>::inverse() const {
		static_assert(W == H, "Triying to get the inverse of a matrix not being a square");
		return this->adj() / this->det();
	}

	template<unsigned int H, unsigned int W, typename T>
	inline Matrix<H, W, T> Matrix<H, W, T>::cof() const {
		static_assert(W == H, "Triying to get the cofactor of a matrix not being a square");
		Matrix<H, W, T> stm;
		for (unsigned int y = 0; y < H; y++) {
			for (unsigned int x = 0; x < W; x++) {
				stm(y, x) = this->minor(y, x) * ((y + x) % 2 == 0 ? 1.0f : -1.0f);
			}
		}
		return stm;
	}

	template<unsigned int H, unsigned int W, typename T>
	inline Matrix<H, W, T> Matrix<H, W, T>::adj() const {
		static_assert(W == H, "Triying to get the adjunctive of a matrix not being a square");
		return this->cof().transpose();
	}


	template<unsigned int H, unsigned int W, typename T>
	inline Matrix<H, W, T> Matrix<H, W, T>::identity() {
		Matrix<H, W, T> stm;
		for (int i = 0; i < fmin(H, W); i++)
			stm(i, i) = 1;
		return stm;
	}


}

#undef GET
