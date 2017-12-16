#include "MathF.h"

// �� ������ ���� ���ϱ�
float UTILITY::Angle(const VECTOR3& dst, const VECTOR3& src)
{
	return D3DXToDegree(acos(D3DXVec3Dot(&dst.Normalized(), &src.Normalized())));
}

// (1, 0) ���͸� �������� ������ ���� ���ϱ�
float UTILITY::Angle(const VECTOR3& dst)
{
	static const VECTOR3 Axis(1, 0, 0);
	float angle = Angle(dst, Axis);
	if (dst.y < 0)
		return 360 - angle;
	return angle;
}

// �ش� ���͸� ���ϴ� ����
float UTILITY::ToTarget(const VECTOR3& dst, const VECTOR3& target)
{
	return Angle(target - dst);
}

// �ش� �� ���̷� ����
int UTILITY::Clamp(int data, int min, int max)
{
	if (data < min)
		return min;
	if (data > max)
		return max;
	return data;
}

// �ش� �� ���̷� ����
double UTILITY::Clamp(double data, double min, double max)
{
	if (data < min)
		return min;
	if (data > max)
		return max;
	return data;
}

// �ش� �� ���̷� ��ȯ
int UTILITY::ClampCycle(int data, int min, int max)
{
	if (data < min)
		return max;
	if (data > max)
		return min;
	return data;
}

// �ش� �� ���̷� ��ȯ
double UTILITY::ClampCycle(double data, double min, double max)
{
	if (data < min)
		return max;
	if (data > max)
		return min;
	return data;
}

// ���� ����
int UTILITY::Lerp(double rate, int begin, int end)
{
	return (end - begin) * rate + begin;
}

// ���� ����
double UTILITY::Lerp(double rate, double begin, double end)
{
	return (end - begin) * rate + begin;
}

// ���� ����(����)
UTILITY::VECTOR3 UTILITY::Lerp(double rate, const VECTOR3& begin, const VECTOR3& end)
{
	return (end - begin) * rate + begin;
}

// ���� ����(���)
UTILITY::MATRIX UTILITY::Lerp(double rate, const MATRIX& begin, const MATRIX& end)
{
	return D3DXMATRIX(
		(end._11 - begin._11) * rate + begin._11,
		(end._12 - begin._12) * rate + begin._12,
		(end._13 - begin._13) * rate + begin._13,
		(end._14 - begin._14) * rate + begin._14,
		(end._21 - begin._21) * rate + begin._21,
		(end._22 - begin._22) * rate + begin._22,
		(end._23 - begin._23) * rate + begin._23,
		(end._24 - begin._24) * rate + begin._24,
		(end._31 - begin._31) * rate + begin._31,
		(end._32 - begin._32) * rate + begin._32,
		(end._33 - begin._33) * rate + begin._33,
		(end._34 - begin._34) * rate + begin._34,
		(end._41 - begin._41) * rate + begin._41,
		(end._42 - begin._42) * rate + begin._42,
		(end._43 - begin._43) * rate + begin._43,
		(end._44 - begin._44) * rate + begin._44
	);
}