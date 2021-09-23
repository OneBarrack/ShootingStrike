#include "Bullet.h"
#include "ObjectManager.h"
#include "MathManager.h"
#include "Bridge.h"
#include "Player.h"
#include "Enemy.h"

Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}


void Bullet::Initialize()
{
	Owner = nullptr;

	TransInfo.Position = Vector3(0.0f, 0.0f);
	TransInfo.Direction = Vector3(0.0f, -1.0f);
	TransInfo.Scale = Vector3(30.0f, 30.0f);
	
	Collider.Position = TransInfo.Position;
	Collider.Scale = TransInfo.Scale;

	Key = eObjectKey::BULLET;
	Status = eObjectStatus::ACTIVATED;
	CollisionType = eCollisionType::ELLIPSE;
	bGenerateCollisionEvent = true;

	Speed = 3.0f;
}

void Bullet::Update()
{
	if ( pBridgeObject )
		pBridgeObject->Update(TransInfo);	

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
	if ( pBridgeObject )
	{		
		if ( Owner->GetKey() == _pObject->GetKey() )
			return;

		// ** Bullet의 주체 Object의 데미지를 충돌된 Object에 전달
		switch ( Owner->GetKey() )
		{
			case eObjectKey::PLAYER: static_cast<Player*>(Owner)->ApplyDamage(_pObject, Damage); break;
			case eObjectKey::ENEMY: static_cast<Enemy*>(Owner)->ApplyDamage(_pObject, Damage);	break;
			default: 
				break;
		}
	}
}

bool Bullet::IsOutOfScreen()
{
	if ( TransInfo.Position.x < -100 || WindowsWidth + 100 < TransInfo.Position.x ||
		TransInfo.Position.y < -100 || WindowsHeight + 100 < TransInfo.Position.y )
		return true;

	return false;
}