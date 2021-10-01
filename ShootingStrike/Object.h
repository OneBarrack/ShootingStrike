#pragma once
#include "Headers.h"

class Bridge;
class Object
{
protected:
	// ** Bitmap Image
	Bitmap* pImage;

	// ** Tag Name
	eTagName tagName;

	// ** 분할 Bitmap에서 현재 적용할 이미지의 Offset
	Point imageOffsetOrder;

	// ** Bridge Object
	Bridge* pBridge;

	// ** 오브젝트의 기본 Transform
	Transform transInfo;

	// ** 충돌체의  기본 Transform
	Transform collider;

	eObjectKey key;
	eObjectStatus status;
	eCollisionType collisionType;

	// ** 모든 오브젝트에 대한 충돌 체크가 필요한 오브젝트인지
	bool bGenerateCollisionEvent;

	// ** Object Speed
	float speed;

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render(HDC _hdc);
	virtual void Release();

	virtual Object* Clone()PURE;

	virtual void OnCollision(Object* _pObject)PURE;

public:
	// ** 이미지를 반환
	Bitmap* GetImage() { return pImage; }

	// ** 태그명 반환
	eTagName GetTagName() { return tagName; }

	// ** 현재 적용할 이미지의 Offset 반환
	Point GetImageOffsetOrder() { return imageOffsetOrder; }

	// ** BridgeObject를 반환
	Bridge* GetBridgeObject() { return pBridge; }

	// ** 오브젝트의 Key 값을 out
	eObjectKey GetKey() const { return key; }

	// ** 오브젝트의 활성화 상태 반환
	eObjectStatus GetStatus() const { return status; }	

	// ** 오브젝트의 충돌체 타입 반환
	eCollisionType GetCollisionType() const { return collisionType; }

	// ** Transform 정보를 out
	Transform GetTransInfo() { return transInfo; }

	// ** 좌표를 Vector3로 out
	Vector3 GetPosition() { return transInfo.Position; }

	// ** 크기를 Vector3로 out
	Vector3 GetScale() { return transInfo.Scale; }

	// ** 방향를 Vector3로 out
	Vector3 GetDirection() { return transInfo.Direction; }

	// ** 충돌체를 out.
	RECT GetColliderL();
	RectF GetColliderF();
	Transform GetCollider() { return collider; }
	Vector3 GetColliderPosition() { return collider.Position; }
	Vector3 GetColliderScale() { return collider.Scale; }

	// ** 오브젝트의 속도 반환
	float GetSpeed() { return speed; }

	// ** 오든 오브젝트에 대한 충돌 체크가 필요한지 확인
	bool IsGeneratedCollisionEvent() { return bGenerateCollisionEvent; }

	// ** 키 입력 상태 반환
	bool CheckKeyInputStatus(eInputKey _inputKey, eKeyInputState _status);

	// ** 이미지 적재
	void SetImage(eImageKey _imageKey);

	// ** 태그명 설정
	void SetTagName(eTagName _tagName) { tagName = _tagName; }

	// ** 현재 적용할 이미지의 Offset 설정
	void SetImageOffsetOrder(Point _order) { imageOffsetOrder = _order; }

	// ** Bridge를 Setting
	void SetBridge(Bridge* _pBridge);

	// ** Transform 정보를 Setting (Transform)
	void SetTransInfo(Transform _transInfo) { transInfo = _transInfo; }

	// ** 좌표를 Setting (Vector3)
	void SetPosition(Vector3 _position) { transInfo.Position = _position; }	
	void SetPosition(float _x, float _y) { transInfo.Position.x = _x; transInfo.Position.y = _y; }

	// ** Scale을 Setting (Vector3)
	void SetScale(Vector3 _Scale) { transInfo.Scale = _Scale; }
	void SetScale(float _x, float _y) { transInfo.Scale.x = _x; transInfo.Scale.y = _y; }

	// ** 좌표를 Setting (Vector3)
	void SetDirection(Vector3 _Direction) { transInfo.Direction = _Direction; }
	void SetDirection(float _x, float _y) { transInfo.Direction.x = _x; transInfo.Direction.y = _y; }

	// ** 충돌체 Transform Setting
	void SetCollider(Transform _collider) { collider = _collider; }
	void SetCollider(Vector3 _position, Vector3 _scale) { collider.Position = _position; collider.Scale = _scale; }

	// ** 충돌체 Position Setting
	void SetColliderPosition(Vector3 _position) { collider.Position = _position; }
	void SetColliderPosition(float _x, float _y) { collider.Position.x = _x; collider.Position.y = _y; }

	// ** 충돌체 Scale Setting
	void SetColliderScale(Vector3 _scale) { collider.Scale = _scale; }
	void SetColliderScale(float _x, float _y) { collider.Scale.x = _x; collider.Scale.y = _y; }

	// ** 오브젝트의 활성화 상태 Setting 
	void SetStatus(const eObjectStatus& _status);

	// ** 오브젝트의 속도 Setting
	void SetSpeed(float _speed) { speed = _speed; }

	// ** 모든 오브젝트에 대한 충돌 체크 필요여부 Setting
	void SetGenerateCollisionEvent(bool _generateCollisionEvent) { bGenerateCollisionEvent = _generateCollisionEvent; }

public:
	Object();
	Object(const Transform& _rTransInfo) : transInfo(_rTransInfo) { }
	virtual ~Object();
};