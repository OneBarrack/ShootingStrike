#include "Bullet.h"
#include "ObjectManager.h"
#include "MathManager.h"
#include "CollisionManager.h"
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
	
	// ** Stage 전장을 벗어났는지 체크
	CheckPositionInBkgBoundary();

	// ** 충돌체 갱신
	SetCollider(TransInfo);
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

	SetStatus(eObjectStatus::DESTROYED);
}

void Bullet::CheckPositionInBkgBoundary()
{
	// ** Stage 전장 배경
	Object* pBackground = ObjectManager::GetInstance()->FindObjectWithTag(eObjectKey::BACKGROUND, eTagName::STAGE_MAIN_BKG);

	// ** Stage의 바운더리
	RectF BkgBoundary = pBackground->GetColliderF();

	// ** Stage 바운더리 기준으로 Check 범위를 추가/감소 시킬 Offset
	float Offset = 0.0f;

	// ** 바운더리 크기 조정
	BkgBoundary.Left   -= Offset;
	BkgBoundary.Top	   -= Offset;
	BkgBoundary.Right  += Offset;
	BkgBoundary.Bottom += Offset;

	// ** Stage의 바운더리 내 Position이 위치하지 않으면 Destroy
	if ( !CollisionManager::IsPointInRect(BkgBoundary, TransInfo.Position) )
	{
		SetStatus(eObjectStatus::DESTROYED);
	}
}