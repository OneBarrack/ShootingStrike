#pragma once

struct Vector3
{
	float x, y, z;

	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	
	Vector3(float _x, float  _y) : x(_x), y(_y), z(0.0f) {}
	
	Vector3(float _x, float  _y, float _z) : x(_x), y(_y), z(_z) {}

	Vector3 operator+ (float _value) { return Vector3(x + _value, y + _value, z + _value); }
	Vector3 operator- (float _value) { return Vector3(x - _value, y - _value, z - _value); }
	Vector3 operator* (float _value) { return Vector3(x * _value, y * _value, z * _value); }
	Vector3 operator/ (float _value) { return Vector3(x / _value, y / _value, z / _value); }

	Vector3 operator+ (Vector3 _v) { return Vector3(x + _v.x, y + _v.y); }
	Vector3 operator- (Vector3 _v) { return Vector3(x - _v.x, y - _v.y); }
	Vector3 operator* (Vector3 _v) { return Vector3(x * _v.x, y * _v.y); }
	Vector3 operator/ (Vector3 _v) { return Vector3(x / _v.x, y / _v.y); }

	bool operator<  (Vector3 _v) { return ((int)x <  (int)_v.x && (int)y <  (int)_v.y); }
	bool operator<= (Vector3 _v) { return ((int)x <= (int)_v.x && (int)y <= (int)_v.y); }
	bool operator>  (Vector3 _v) { return ((int)x >  (int)_v.x && (int)y >  (int)_v.y); }
	bool operator>= (Vector3 _v) { return ((int)x >= (int)_v.x && (int)y >= (int)_v.y); }
	bool operator== (Vector3 _v) { return ((int)x == (int)_v.x && (int)y == (int)_v.y); }
};

struct Transform
{
	Vector3 Position;
	Vector3 Scale;
	Vector3 Direction;

	Transform() : 
		Position(Vector3()), Scale(Vector3()), Direction(Vector3()) {}

	Transform(Vector3 _position, Vector3 _scale) : 
		Position(_position), Scale(_scale), Direction(Vector3()) {}

	Transform(Vector3 _position, Vector3 _scale, Vector3 _direction) :
		Position(_position), Scale(_scale), Direction(_direction) {}

	Transform(float _Px, float _Py, float _Sx, float _Sy) :
		Position(Vector3(_Px, _Py)), Scale(Vector3(_Sx, _Sy)), Direction(Vector3())	{}

	Transform(float _Px, float _Py, float _Sx, float _Sy, float _Dx, float _Dy) :
		Position(Vector3(_Px, _Py)), Scale(Vector3(_Sx, _Sy)), Direction(Vector3(_Dx, _Dy)) {}	
};

struct Point
{
	int x, y;

	Point() : x(0), y(0) {}
	Point(int _x, int _y) : x(_x), y(_y) {}
};

struct PointF
{
	float x, y;

	PointF() : x(0.0f), y(0.0f) {}
	PointF(float _x, float  _y) : x(_x), y(_y) {}
};

struct Rect
{
	int Left;
	int Top;
	int Right;
	int Bottom;

	Rect() : Left(0), Top(0), Right(0), Bottom(0) {}
	Rect(int _left, int _top, int _right, int _bottom) :
		Left(_left), Top(_top), Right(_right), Bottom(_bottom) {}
};

struct RectF
{
	float Left;
	float Top;
	float Right;
	float Bottom;

	RectF() : Left(0.0f), Top(0.0f), Right(0.0f), Bottom(0.0f) {}
	RectF(float _left, float _top, float _right, float _bottom) : 
		Left(_left), Top(_top), Right(_right), Bottom(_bottom) {}
};