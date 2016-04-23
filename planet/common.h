#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include <glm\glm.hpp>

#include "log.h"

namespace planet {
	using namespace std;
	using namespace glm;

	template<typename T>
	inline bool insideRange(T value, T min, T max) {
		return min <= value && value <= max;
	}
}