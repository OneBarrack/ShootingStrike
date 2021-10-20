#include "Effect.h"

#include "UserInterface.h"

Effect::Effect()
{

}

Effect::~Effect()
{
}


void Effect::Initialize()
{
	Super::Initialize();	

	objectKey = eObjectKey::EFFECT;
	objectStatus = eObjectStatus::ACTIVATED;
	collisionType = eCollisionType::NONE;

	bGenerateCollisionEvent = false;
}

void Effect::Update()
{
	Super::Update();
}

void Effect::Render(HDC _hdc)
{
	Super::Render(_hdc);
}

void Effect::Release()
{
	Super::Release();
}

void Effect::OnCollision(Object* _pObject)
{

}
