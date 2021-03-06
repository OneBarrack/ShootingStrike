#include "UserInterface.h"

UserInterface::UserInterface()
{

}

UserInterface::~UserInterface()
{
}


void UserInterface::Initialize()
{
	Super::Initialize();

	objectKey = eObjectKey::UI;
	objectStatus = eObjectStatus::ACTIVATED;
	collisionType = eCollisionType::NONE;

	bGenerateCollisionEvent = false;
}

void UserInterface::Update()
{
	Super::Update();
}

void UserInterface::Render(HDC _hdc)
{
	Super::Render(_hdc);
}

void UserInterface::Release()
{
	Super::Release();
}

void UserInterface::OnCollision(Object* _pObject)
{

}