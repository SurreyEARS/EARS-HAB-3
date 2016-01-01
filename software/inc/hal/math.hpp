/*
 * math.hpp
 *
 *  Created on: Dec 26, 2015
 *      Author: James
 */

#pragma once

#include <cmath>

__attribute__((always_inline)) inline float lerp(float v0, float v1, float t)
{
	return (1 - t) * v0 + t * v1;
}
