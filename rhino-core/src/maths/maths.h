#pragma once

#include "Transform.h"
#include "Color.h"

namespace rhino {

	template<typename T>
	constexpr inline const T min(const T val, const T min) {
		return val < min ? val : max;
	}

	template<typename T>
	constexpr inline const T max(const T val, const T max) {
		return val > max ? val : max;
	}

	template<typename T>
	constexpr inline const T clamp(const T val, const T min, const T max) {
		return min(max(val, min), max);
	}

	template<typename T>
	constexpr inline const bool inRange(const T val, const T min, const T max) {
		return val >= min && val <= max;
	}

	template<typename T>
	constexpr inline const bool doRangesOverlap(const T r1Min, const T r1Max, const T r2Min, const T r2Max) {
		return r1Max >= r2Min && r1Min <= r2Max;
	}

}
