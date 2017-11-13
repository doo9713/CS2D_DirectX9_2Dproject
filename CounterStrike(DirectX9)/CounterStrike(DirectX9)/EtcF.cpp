#include "EtcF.h"
#include "MathF.h"
#include "Constant.h"

// 최소값 반환
float UTILITY::MinList(std::initializer_list<float> min)
{
	float result = min.begin()[0];
	for (auto data : min)
	{
		if (data < result)
			result = data;
	}
	return result;
}

// 최대값 반환
float UTILITY::MaxList(std::initializer_list<float> max)
{
	float result = max.begin()[0];
	for (auto data : max)
	{
		if (data > result)
			result = data;
	}
	return result;
}

// 최소값 인덱스 반환
int UTILITY::MinIndex(std::initializer_list<float> min)
{
	int Idx = 0;
	float MinData = min.begin()[0];
	int MaxSize = min.size();
	for (int i = 0; i < MaxSize; ++i)
	{
		if (MinData > min.begin()[i])
		{
			MinData = min.begin()[i];
			Idx = i;
		}
	}
	return Idx;
}

// 최대값 인덱스 반환
int UTILITY::MaxIndex(std::initializer_list<float> max)
{
	int Idx = 0;
	float MaxData = max.begin()[0];
	int MaxSize = max.size();
	for (int i = 0; i < MaxSize; ++i)
	{
		if (MaxData < max.begin()[i])
		{
			MaxData = max.begin()[i];
			Idx = i;
		}
	}
	return Idx;
}

std::mt19937_64 Engine;

// 난수 출력
int UTILITY::Random(int Min, int Max)
{
	std::random_device Dev;
	Engine.seed(Dev());
	std::uniform_int_distribution<int> Sub(Min, Max);
	return Sub(Engine);
}

// 난수 출력
double UTILITY::Random(double Min, double Max)
{
	std::random_device Dev;
	Engine.seed(Dev());
	std::uniform_real_distribution<double> Sub(Min, Max);
	return Sub(Engine);
}

// 마우스의 좌표를 DirectX 좌표계로 전환
UTILITY::VECTOR3 UTILITY::GetMousePosition()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	return VECTOR3(pt.x - ScreenWidth * 0.5, (pt.y - ScreenHeight * 0.5) * -1);
}