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
	TransInfo.Direction = Vector3(0.0f, -1.0f);
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

	//Target = ObjectManager::GetInstance()->GetTarget(TransInfo.Position);

	//if (Target)
	//	TransInfo.Direction = MathManager::GetDirection(TransInfo.Position, Target->GetPosition());	

	if ( IsOutOfScreen() )
	{
		Status = eObjectStatus::DESTROYED;		
	}
}

void Bullet::Render(HDC _hdc)
{
	if ( pBridgeObject )
		pBridgeObject->Render(_hdc);
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

bool Bullet::IsOutOfScreen()
{
	if ( TransInfo.Position.x < -100 || WindowsWidth + 100 < TransInfo.Position.x ||
		TransInfo.Position.y < -100 || WindowsHeight + 100 < TransInfo.Position.y )
		return true;

	return false;
}