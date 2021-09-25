#include "Bullet.h"
#include "ObjectManager.h"
#include "MathManager.h"
#include "Bridge.h"
#include "Player.h"
#include "Enemy.h"

Bullet::Bullet()
	: pOwner(nullptr)
	, Damage(0)
{

}

Bullet::~Bullet()
{
	Release();
}


void Bullet::Initialize()
{
	pOwner = nullptr;

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
		pBridgeObject->Update();
	
	// ** 충돌체 갱신
	Collider = TransInfo;
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
		if ( pOwner->GetKey() == _pObject->GetKey() )
			return;

		// ** Bullet의 주체 Object의 데미지를 충돌된 Object에 전달
		switch ( pOwner->GetKey() )
		{
			case eObjectKey::PLAYER: static_cast<Player*>(pOwner)->ApplyDamage(_pObject, Damage); break;
			case eObjectKey::ENEMY: static_cast<Enemy*>(pOwner)->ApplyDamage(_pObject, Damage);	break;
			default: 
				break;
		}
	}
}