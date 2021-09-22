#pragma once
#include "Headers.h"

class Bridge;
class Object
{
protected:
	// ** Bridge Object
	Bridge* pBridgeObject;

	// ** 오브젝트의 기본 Transform
	Transform TransInfo;

	// ** 충돌체의  기본 Transform
	Transform Collider;
	Vector3 Offset;

	eObjectKey Key;
	eObjectStatus Status;
	eCollisionType CollisionType;
	float Speed;

	// ** 모든 오브젝트에 대한 충돌 체크가 필요한 오브젝트인지
	bool bGenerateCollisionEvent;
public:
	virtual void Initialize()PURE;
	virtual void Update()PURE;
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

	// ** 오든 오브젝트에 대한 충돌 체크가 필요한지 확인
	bool IsGeneratedCollisionEvent() { return bGenerateCollisionEvent; }

	// ** 키 입력 상태 반환
	bool CheckKeyInputStatus(eInputKey _InputKey, eKeyInputStatus _Status);

	// ** BridgeObject를 Setting
	void SetBridgeObject(Bridge* _pBridge) { pBridgeObject = _pBridge; }

	// ** 좌표를 Setting (Vector3)
	void SetPosition(Vector3 _position) { TransInfo.Position = _position; }	
	void SetPosition(float _x, float _y) { TransInfo.Position.x = _x; TransInfo.Position.y = _y; }

	// ** Scale을 Setting (Vector3)
	void SetScale(Vector3 _Scale) { TransInfo.Scale = _Scale; }
	void SetScale(float _x, float _y) { TransInfo.Scale.x = _x; TransInfo.Scale.y = _y; }

	// ** 충돌체 Position Setting
	void SetColliderPosition(Vector3 _position) { Collider.Position = _position; }
	void SetColliderPosition(float _x, float _y) { Collider.Position.x = _x; Collider.Position.y = _y; }

	// ** 충돌체 Scale Setting
	void SetColliderScale(Vector3 _Scale) { Collider.Scale = _Scale; }
	void SetColliderScale(float _x, float _y) { Collider.Scale.x = _x; Collider.Scale.y = _y; }

	// ** 오브젝트의 활성화 상태 Setting 
	void SetStatus(const eObjectStatus& _Status);

	// ** 모든 오브젝트에 대한 충돌 체크 필요여부 Setting
	void SetGenerateCollisionEvent(bool _GenerateCollisionEvent) { bGenerateCollisionEvent = _GenerateCollisionEvent; }

public:
	Object();
	Object(const Transform& _rTransInfo) : TransInfo(_rTransInfo) { }
	virtual ~Object();
};