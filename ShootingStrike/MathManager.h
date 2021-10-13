#pragma once
#include "Headers.h"

class MathManager
{
public:
	// ** 거리를 구하는 함수
	static float GetDistance(Vector3 _start, Vector3 _dest)
	{
		// ** _Current 와 _Target 사이의 밑변과 높이를 구함.
		float fX = _dest.x - _start.x;
		float fY = _dest.y - _start.y;

		// ** 빗변을 반환
		return sqrt((fX * fX) + (fY * fY));
	}

	// ** 방향을 구하는 함수
	static Vector3 GetDirection(Vector3 _start, Vector3 _dest)
	{
		// ** _Current 와 _Target 사이의 밑변과 높이를 구함.
		float fX = _dest.x - _start.x;
		float fY = _dest.y - _start.y;

		// ** 빗변을 구함.
		float distance = sqrt((fX * fX) + (fY * fY));

		// ** 방향만 남겨두기 위해 빗변으로 나눠준다.
		if ( distance > 0.0f )
			return Vector3(fX / distance, fY / distance);
		else
			return Vector3(0.0f, 0.0f);
		// ** 설명 
		// ** 직각인 삼각형이 있을때 빗변은 항상 밑변이나 높이보다 크다.
		// ** 자기 자신보다 큰값으로 나눠진다면 값은 1보다 작은 값이 나온다.
		// ** Vector 에서 1이거나 1보다 작은 값은 방향만 남아있다고 본다.
		// ** 1 이라는 값에 어떤값을 곱하더라도 같은 값이 나오기 때문이다.
	}

	// ** Convert degree to radian
	static float DegreeToRadian(int _degree) { return _degree * PI / 180; }
	static float DegreeToRadian(float _degree) { return _degree * PI / 180; }

	// ** Convert radian to degree
	static int RadianToDegree(float _radian) { return static_cast<int>(_radian * 180 / PI); }

	// ** Rotate vector by degree
	static Vector3 RotateByDegree(Vector3 _v, float _degree) 
	{
		return Vector3(
			(_v.x * cosf(DegreeToRadian(_degree))) - (_v.y * sinf(DegreeToRadian(_degree))),
			(_v.x * sinf(DegreeToRadian(_degree))) + (_v.y * cosf(DegreeToRadian(_degree))));
	}

	// ** Rotate vector by radian
	static Vector3 RotateByRadian(Vector3 _v, float _radian)
	{
		return Vector3(
			(_v.x * cosf(_radian)) - (_v.y * sinf(_radian)),
			(_v.x * sinf(_radian)) + (_v.y * cosf(_radian)));
	}
};

