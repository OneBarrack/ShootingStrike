#include "Background.h"
#include "Bridge.h"

Background::Background()
{

}

Background::~Background()
{

}


void Background::Initialize()
{
	TransInfo.Position = Vector3(0.0f, 0.0f);
	TransInfo.Direction = Vector3(0.0f, 0.0f);
	TransInfo.Scale = Vector3(0.0f, 0.0f);

	Key = eObjectKey::BACKGROUND;
	Status = eObjectStatus::ACTIVATED;
	CollisionType = eCollisionType::NONE;
	bGenerateCollisionEvent = false;

	pBridgeObject = nullptr;
}

void Background::Update()
{
	if ( pBridgeObject )
		pBridgeObject->Update(TransInfo);
}

void Background::Render(HDC _hdc)
{
	if ( pBridgeObject )
		pBridgeObject->Render(_hdc);
}

void Background::Release()
{
	if ( pBridgeObject )
	{
		pBridgeObject->Release();
		::Safe_Delete(pBridgeObject);
	}
}

void Background::OnCollision(Object* _pObject)
{
}
