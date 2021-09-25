#pragma once

struct Vector3
{
	float x, y, z;

	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	
	Vector3(float _x, float  _y) : x(_x), y(_y), z(0.0f) {}
	
	Vector3(float _x, float  _y, float _z) : x(_x), y(_y), z(_z) {}

	Vector3 operator+ (Vector3& v) { return Vector3(x + v.x, y + v.y); }
	Vector3 operator- (Vector3& v) { return Vector3(x - v.x, y - v.y); }
	Vector3 operator* (Vector3& v) { return Vector3(x * v.x, y * v.y); }
	Vector3 operator/ (Vector3& v) { return Vector3(x / v.x, y / v.y); }
	bool operator== (Vector3& v) { return ((int)x == (int)v.x && (int)y == (int)v.y); }
};

struct Transform
{
	Vector3 Position;
	Vector3 Scale;
	Vector3 Direction;

	Transform() : 
		Position(Vector3()), Scale(Vector3()), Direction(Vector3()) {}

	Transform(Vector3 _Position, Vector3 _Scale) : 
		Position(_Position), Scale(_Scale), Direction(Vector3()) {}

	Transform(Vector3 _Position, Vector3 _Scale, Vector3 _Direction) :
		Position(_Position), Scale(_Scale), Direction(_Direction) {}

	Transform(float _Px, float _Py, float _Sx, float _Sy) :
		Position(Vector3(_Px, _Py)), Scale(Vector3(_Sx, _Sy)), Direction(Vector3())	{}

	Transform(float _Px, float _Py, float _Sx, float _Sy, float _Dx, float _Dy) :
		Position(Vector3(_Px, _Py)), Scale(Vector3(_Sx, _Sy)), Direction(Vector3(_Dx, _Dy)) {}	
};

struct PointF
{
	float x, y;

	PointF(float _x, float  _y) : x(_x), y(_y) {}
};

struct RectF
{
	float Left;
	float Top;
	float Right;
	float Bottom;

	RectF(float _Left, float _Top, float _Right, float _Bottom) : 
		Left(_Left), Top(_Top), Right(_Right), Bottom(_Bottom) {}
};