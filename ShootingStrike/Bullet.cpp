#include "Bullet.h"
#include "ObjectManager.h"
#include "MathManager.h"
#include "Bridge.h"

Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}


void Bullet::Initialize()
{
	TransInfo.Position = Vector3(0.0f, 0.0f);
	TransInfo.Direction = Vector3(1.0f, 0.0f);
	TransInfo.Scale = Vector3(30.0f, 30.0f);

	Key = eObjectKey::BULLET;
	Status = eObjectStatus::ACTIVATED;
	CollisionType = eCollisionType::ELLIPSE;

	Speed = 3.0f;

	Target = ObjectManager::GetInstance()->GetTarget(TransInfo.Position);
}

void Bullet::Update()
{
	if ( pBridgeObject )
		pBridgeObject->Update(TransInfo);

	Target = ObjectManager::GetInstance()->GetTarget(TransInfo.Position);

	if (Target)
		TransInfo.Direction = MathManager::GetDirection(TransInfo.Position, Target->GetPosition());	

	TransInfo.Position.x += TransInfo.Direction.x * Speed;
	TransInfo.Position.y += TransInfo.Direction.y * Speed;

	if ( TransInfo.Position.x >= (WindowsWidth - 100) )
		return;
}

void Bullet::Render(HDC _hdc)
{
	if ( pBridgeObject )
		pBridgeObject->Render(_hdc);

	Ellipse(_hdc,
		int(TransInfo.Position.x - (TransInfo.Scale.x / 2)),
		int(TransInfo.Position.y - (TransInfo.Scale.x / 2)),
		int(TransInfo.Position.x + (TransInfo.Scale.x / 2)),
		int(TransInfo.Position.y + (TransInfo.Scale.x / 2)));
}

void Bullet::Release()
{
	if ( pBridgeObject )
	{
		pBridgeObject->Release();
		::Safe_Delete(pBridgeObject);
	}
}

void Bullet::OnCollision(Object* _pObject)
{
}
