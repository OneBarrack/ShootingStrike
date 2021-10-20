#include "Bullet.h"
#include "ObjectManager.h"
#include "MathManager.h"
#include "CollisionManager.h"
#include "Bridge.h"
#include "Player.h"
#include "Enemy.h"

Bullet::Bullet()
	: pOwner(nullptr)
	, damage(0)
{

}

Bullet::~Bullet()
{
}


void Bullet::Initialize()
{
	Super::Initialize();

	// ** 임시 빨간색 총알
	imageOffsetOrder = { 1, 0 };

	objectKey = eObjectKey::BULLET;
	objectStatus = eObjectStatus::ACTIVATED;
	collisionType = eCollisionType::ELLIPSE;
	bGenerateCollisionEvent = true;

	pOwner = nullptr;	
	damage = 0;
}

void Bullet::Update()
{
	Super::Update();
	
	// ** Stage 전장을 벗어났는지 체크
	CheckPositionInBkgBoundary();

	// ** 충돌체 갱신
	SetCollider(transInfo);
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
		// ** 같은 Object거나 Item과 충돌시 충돌처리 하지 않음
		if ( _pObject->GetKey() == pOwner->GetKey() || 
			_pObject->GetKey() == eObjectKey::ITEM )
			return;

		// ** Bullet의 주체 Object의 데미지를 충돌된 Object에 전달
		switch ( pOwner->GetKey() )
		{
			case eObjectKey::PLAYER: 
				static_cast<Player*>(pOwner)->ApplyDamage(_pObject, damage); 
				SetStatus(eObjectStatus::DESTROYED); 
				break;
			case eObjectKey::ENEMY: 
				static_cast<Enemy*>(pOwner)->ApplyDamage(_pObject, damage);	
				SetStatus(eObjectStatus::DESTROYED); 
				break;
			default: 
				break;
		}
	}	
}

void Bullet::CheckPositionInBkgBoundary()
{
	// ** Stage 전장 배경
	Object* pBackground = ObjectManager::GetInstance()->FindObjectWithTag(eObjectKey::BACKGROUND, eTagName::STAGE_MAIN_BKG);

	// ** Stage의 바운더리
	RectF bkgBoundary = pBackground->GetColliderF();

	// ** Stage 바운더리 기준으로 Check 범위를 추가/감소 시킬 Offset
	float offset = 0.0f;

	// ** 바운더리 크기 조정
	bkgBoundary.Left   -= offset;
	bkgBoundary.Top	   -= offset;
	bkgBoundary.Right  += offset;
	bkgBoundary.Bottom += offset;

	// ** Stage의 바운더리 내 Position이 위치하지 않으면 Destroy
	if ( !CollisionManager::IsPointInRect(bkgBoundary, transInfo.Position) )
	{
		SetStatus(eObjectStatus::DESTROYED);
	}
}