#pragma once

struct Vector3
{
	float x, y, z;

	Vector3() : x(0), y(0), z(0) {}

	Vector3(float _x, float  _y) : x(_x), y(_y), z(0) {}

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
};