#pragma once
#include "Headers.h"

class Bitmap;
class Object
{
protected:
	// ** 오브젝트의 기본 Transform
	Transform TransInfo;

	// ** 충돌체의  기본 Transform
	Transform Collider;
	Vector3 Offset;

	eObjectKey Key;
	eObjectStatus Status;
	eCollisionType CollisionType;
	float Speed;

	//Object* Target;
public:
	virtual void Initialize()PURE;
	virtual int Update()PURE;
	virtual void Render(HDC _hdc)PURE;
	virtual void Release()PURE;
	virtual void OnCollision(Object* _pObject)PURE;

	virtual Object* Clone()PURE;

public:
	// ** 이미지를 출력하는데 사용하는 Key 값을 out
	eObjectKey GetKey() const { return Key; }

	// ** 오브젝트의 활성화 상태 반환
	eObjectStatus GetStatus() const { return Status; }	

	// ** 오브젝트의 충돌체 타입 반환
	eCollisionType GetCollisionType() const { return CollisionType; }

	// ** 좌표를 Vector3로 out
	Vector3 GetPosition() { return TransInfo.Position; }

	// ** 크기를 Vector3로 out
	Vector3 GetScale() { return TransInfo.Scale; }

	// ** 충돌체를 out.
	RECT GetCollider();
	
	Vector3 GetColliderPosition() { return Collider.Position; }
	Transform GetColliderTransform() { return Collider; }

	// ** 좌표를 Setting (Vector3)
	void SetPosition(Vector3 _position) { TransInfo.Position = _position; }

	// ** 좌표를 Setting (_x, _y)
	void SetPosition(float _x, float _y) { TransInfo.Position.x = _x; TransInfo.Position.y = _y; }

	// ** 충돌체를 Setting
	void SetColliderPosition(float _x, float _y) { Collider.Position.x = _x; Collider.Position.y = _y; }

	// ** 오브젝트의 활성화 상태 Setting 
	void SetStatus(const eObjectStatus& _Status) { Status = _Status; }
public:
	Object();
	Object(const Transform& _rTransInfo) : TransInfo(_rTransInfo) { }
	virtual ~Object();
};