#include "Object.h"
#include "Bridge.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "BitmapManager.h"

Object::Object()
	: pImage(nullptr)
	, ImageOffsetOrder(Point(0,0))
	, pBridge(nullptr)
	, TransInfo(Transform())
	, Collider(Transform())
	, Offset(Vector3())
	, Key(eObjectKey::NONE)
	, Status(eObjectStatus::ACTIVATED)
	, CollisionType(eCollisionType::NONE)
	, Speed(0.0f)
	, bGenerateCollisionEvent(false)
{
}

Object::~Object()
{

}

void Object::Initialize()
{
	pImage = nullptr;
	ImageOffsetOrder = Point(0, 0);
	pBridge = nullptr;
	TransInfo = Transform();
	Collider = Transform();
	Offset = Vector3();
	Key = eObjectKey::NONE;
	Status = eObjectStatus::ACTIVATED;
	CollisionType = eCollisionType::NONE;
	Speed = 0.0f;
	bGenerateCollisionEvent = false;
}

void Object::Update()
{
	if ( pBridge ) 
		pBridge->Update();
}

void Object::Render(HDC _hdc)
{
	if ( pBridge ) 
		pBridge->Render(_hdc);
}

void Object::Release()
{
	if ( pBridge ) 
		ObjectManager::GetInstance()->RecallBridge(pBridge);
}

RECT Object::GetColliderL()
{	
	return RECT{
		LONG(Collider.Position.x - (Collider.Scale.x * 0.5f)),
		LONG(Collider.Position.y - (Collider.Scale.y * 0.5f)),
		LONG(Collider.Position.x + (Collider.Scale.x * 0.5f)),
		LONG(Collider.Position.y + (Collider.Scale.y * 0.5f))};
}

RectF Object::GetColliderF()
{
	return RectF{
		Collider.Position.x - (Collider.Scale.x * 0.5f),
		Collider.Position.y - (Collider.Scale.y * 0.5f),
		Collider.Position.x + (Collider.Scale.x * 0.5f),
		Collider.Position.y + (Collider.Scale.y * 0.5f)};
}

bool Object::CheckKeyInputStatus(eInputKey _InputKey, eKeyInputState _Status)
{
	return (InputManager::GetInstance()->GetKeyState(_InputKey) == _Status);
	
}

void Object::SetImage(eImageKey _ImageKey)
{
	pImage = BitmapManager::GetInstance()->GetImage(_ImageKey);
}

void Object::SetBridge(Bridge* _pBridge)
{
	// ** 받은 Bridge가 null이 아니면
	if ( _pBridge )
	{
		// ** 기존 Bridge가 존재한다면 Recall
		if ( pBridge ) ObjectManager::GetInstance()->RecallBridge(pBridge);

		// ** Bridge와 Owner 정보 입력
		_pBridge->SetOwner(this);
		pBridge = _pBridge;
	}
}

void Object::SetStatus(const eObjectStatus& _Status)
{	
	Status = _Status;
	
	// ** ACTIVATED 상태가 아니라면 충돌 체크가 필요하지 않음
	if ( Status != eObjectStatus::ACTIVATED )
	{
		SetGenerateCollisionEvent(false);
	}
}