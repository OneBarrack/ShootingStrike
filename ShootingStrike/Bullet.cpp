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
	Super::Initialize();

	Key = eObjectKey::BULLET;
	Status = eObjectStatus::ACTIVATED;
	CollisionType = eCollisionType::ELLIPSE;
	bGenerateCollisionEvent = true;

	pOwner = nullptr;	
	Damage = 0;
}

void Bullet::Update()
{
	Super::Update();
	
	// ** 충돌체 갱신
	Collider = TransInfo;
}

void Bullet::Render(HDC _hdc)
{
	Super::Render(_hdc);

}

void Bullet::Release()
{
	Super::Release();
}

void Bullet::OnCollision(Object* _pObject)
{
	if ( pBridge )
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