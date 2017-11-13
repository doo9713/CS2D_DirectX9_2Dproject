#pragma once

#include "UtilConstant.h"

namespace UTILITY
{
	struct VECTOR3;

	float MinList(std::initializer_list<float> min);
	float MaxList(std::initializer_list<float> max);
	
	int MinIndex(std::initializer_list<float> min);
	int MaxIndex(std::initializer_list<float> max);

	int Random(int Min, int Max);
	double Random(double Min, double Max);

	VECTOR3 GetMousePosition();
}