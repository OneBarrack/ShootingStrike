#include "Object.h"
#include "InputManager.h"

Object::Object() : pBridgeObject(nullptr)
{

}

Object::~Object()
{

}

RECT Object::GetCollider()
{	
	return RECT{
		LONG(Collider.Position.x - (Collider.Scale.x * 0.5f)) ,
		LONG(Collider.Position.y - (Collider.Scale.y * 0.5f)) ,
		LONG(Collider.Position.x + (Collider.Scale.x * 0.5f)) ,
		LONG(Collider.Position.y + (Collider.Scale.y * 0.5f)) };
}

bool Object::CheckKeyInputStatus(eInputKey _InputKey, eKeyInputStatus _Status)
{
	return (InputManager::GetInstance()->GetKeyStatus(_InputKey) == _Status);
	
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