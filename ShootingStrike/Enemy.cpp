#include "Enemy.h"
#include "Bridge.h"
#include "BitmapManager.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

void Enemy::Initialize()
{
	TransInfo.Position = Vector3(0.0f, 0.0f);
	TransInfo.Scale = Vector3(149.0f, 124.0f);

	Collider.Position = TransInfo.Position;
	Collider.Scale = TransInfo.Scale;

	Offset = Vector3(149.0f, 0.0f);

	Status = eObjectStatus::ACTIVATED;
	Key = eObjectKey::ENEMY;
	CollisionType = eCollisionType::ELLIPSE;
	bGenerateCollisionEvent = true;

	Speed = 1.5f;
}

void Enemy::Update()
{
	if ( pBridgeObject )
		pBridgeObject->Update(TransInfo);

	if( !(Offset.y >= 94) )
		Offset.y += 2.5f;

	return;
}

void Enemy::Render(HDC _hdc)
{
	if ( pBridgeObject )
		pBridgeObject->Render(_hdc);

	//TransparentBlt(_hdc, // ** 최종 출력 위치
	//	int(TransInfo.Position.x - (TransInfo.Scale.x / 2)),
	//	int(TransInfo.Position.y + (TransInfo.Scale.x / 2) - Offset.y - 50),
	//	int(TransInfo.Scale.x),
	//	int(Offset.y),
	//	BitmapManager::GetInstance()->GetImage(eImageKey::MOLE)->GetMemDC(),
	//	0, 0,
	//	int(TransInfo.Scale.x),
	//	int(Offset.y),
	//	RGB(255, 0, 255));
}

void Enemy::Release()
{
	if ( pBridgeObject )
	{
		pBridgeObject->Release();
		::Safe_Delete(pBridgeObject);
	}
}

void Enemy::OnCollision(Object* _pObject)
{
}
