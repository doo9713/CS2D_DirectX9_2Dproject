#pragma once

#include "UtilConstant.h"

namespace UTILITY
{
	struct VECTOR3 : public D3DXVECTOR3
	{
		VECTOR3(float x = 0, float y = 0, float z = 0)
			: D3DXVECTOR3(x, y, z)
		{}
		VECTOR3(const D3DXVECTOR3& vec)
			: D3DXVECTOR3(vec)
		{}

		operator D3DXVECTOR3&()
		{
			return *this;
		}
		operator const D3DXVECTOR3&() const
		{
			return *this;
		}
		const VECTOR3 operator- (VECTOR3 other) const
		{
			VECTOR3 result((*this).x - other.x, (*this).y - other.y, (*this).z - other.z);
			return result;
		}

		float Length() const
		{
			return D3DXVec3Length(this);
		}

		// 백터와 행렬 연산 (x, y, z, 1)
		VECTOR3& TransformCoord(const D3DXMATRIX& matrix)
		{
			D3DXVec3TransformCoord(this, this, &matrix);
			return *this;
		}
		// 백터와 행렬 연산 (x, y, z, 0)
		VECTOR3& TransformNormal(const D3DXMATRIX& matrix)
		{
			D3DXVec3TransformNormal(this, this, &matrix);
			return *this;
		}
		// 정규화 값 복사
		VECTOR3 Normalized() const
		{
			VECTOR3 result;
			D3DXVec3Normalize(&result, this);
			return result;
		}
		// 자신을 정규화
		VECTOR3& Normalize()
		{
			D3DXVec3Normalize(this, this);
			return *this;
		}
		// 백터 회전 값 복사
		VECTOR3 RotationCopy(float Angle) const
		{
			D3DXMATRIX Rot;
			VECTOR3 result;
			D3DXMatrixRotationZ(&Rot, D3DXToRadian(Angle));
			D3DXVec3TransformCoord(&result, this, &Rot);
			return result;
		}
		// 자신을 회전
		VECTOR3& Rotation(float Angle)
		{
			D3DXMATRIX Rot;
			D3DXMatrixRotationZ(&Rot, D3DXToRadian(Angle));
			D3DXVec3TransformCoord(this, this, &Rot);
			return *this;
		}
	};

	struct MATRIX : public D3DXMATRIX
	{
		MATRIX()
		{
			D3DXMatrixIdentity(this);
		}
		MATRIX(const D3DXMATRIX& other)
			: D3DXMATRIX(other)
		{}

		operator D3DXMATRIX&()
		{
			return *this;
		}
		operator const D3DXMATRIX&()
		{
			return *this;
		}

		// 이동행렬(값)
		MATRIX& Move(float x = 0, float y = 0, float z = 0)
		{
			D3DXMatrixTranslation(this, x, y, z);
			return *this;
		}
		// 이동행렬(벡터)
		MATRIX& Move(const VECTOR3& dst)
		{
			D3DXMatrixTranslation(this, dst.x, dst.y, dst.z);
			return *this;
		}
		// 크기행렬(값)
		MATRIX& Scale(float x = 1, float y = 1, float z = 1)
		{
			D3DXMatrixScaling(this, x, y, z);
			return *this;
		}
		// 크기행렬(벡터)
		MATRIX& Scale(const VECTOR3& dst)
		{
			D3DXMatrixScaling(this, dst.x, dst.y, dst.z);
			return *this;
		}
		// 회전행렬
		MATRIX& Rotation(float Angle)
		{
			D3DXMatrixRotationZ(this, D3DXToRadian(Angle));
			return *this;
		}
		// 역행렬
		MATRIX& Inverse()
		{
			D3DXMatrixInverse(this, nullptr, this);
			return *this;
		}
	};

	float Angle(const VECTOR3& dst, const VECTOR3& src);
	float Angle(const VECTOR3& dst);
	float ToTarget(const VECTOR3& dst, const VECTOR3& target);

	int Clamp(int data, int min = 0, int max = 1);
	double Clamp(double data, double min = 0, double max = 1);

	int ClampCycle(int data, int min = 0, int max = 1);
	double ClampCycle(double data, double min = 0, double max = 1);

	int Lerp(double rate, int begin = 0, int end = 1);
	double Lerp(double rate, double begin = 0, double end = 1);
	VECTOR3 Lerp(double rate, const VECTOR3& begin, const VECTOR3& end);
	MATRIX Lerp(double rate, const MATRIX& begin, const MATRIX& end);
}