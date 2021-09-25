#include "Object.h"
#include "InputManager.h"

Object::Object()
	: pBridgeObject(nullptr)
	, TransInfo(Transform())
	, Collider(Transform())
	, Offset(Vector3())
	// , Key(eObjectKey)
	, Status(eObjectStatus::ACTIVATED)
	, CollisionType(eCollisionType::NONE)
	, Speed(0.0f)
	, bGenerateCollisionEvent(false)
{

}

Object::~Object()
{

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

void Object::SetStatus(const eObjectStatus& _Status)
{	
	Status = _Status;
	
	// ** ACTIVATED 상태가 아니라면 충돌 체크가 필요하지 않음
	if ( Status != eObjectStatus::ACTIVATED )
	{
		SetGenerateCollisionEvent(false);
	}
}