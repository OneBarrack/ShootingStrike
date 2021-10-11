#include "Enemy.h"
#include "Bridge.h"
#include "Player.h"
#include "Bullet.h"
#include "BitmapManager.h"
#include "MathManager.h"
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "SpawnManager.h"

Enemy::Enemy()
	: maxHP(0)
	, HP(0)
	, bSpawing(false)
	, bAttacking(false)
	, bTakeDamage(false)
	, bDied(false)
	, hitScore(0)
	, deathScore(0)
	, oldPosition(Vector3())
{

}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	Super::Initialize();

	key = eObjectKey::ENEMY;
	status = eObjectStatus::ACTIVATED;
	collisionType = eCollisionType::RECT;
	oldPosition = transInfo.Position;
	bGenerateCollisionEvent = true;

	maxHP = 50;
	HP = 50;

	bSpawing = false;
	bAttacking = false;
	bTakeDamage = false;
	bDied = false;

	speed = 3.0f;
}

void Enemy::Update()
{
	Super::Update();

	// ** 가속도 적용
	speed += acceleration;
	float aa = acceleration;
	// ** Enemy Update 작업 필요
	
	// ** 스폰 중
	//if ( bSpawing )
	//{
	//	// SpawnEnemy
	//	return;
	//}

	//// ** 죽음
	//if ( bDied )
	//{
	//	bDied = false;
	//	//return;
	//}

	//// ** 피해를 입었을 시
	//if ( bTakeDamage )
	//{

	//}

	// ** 일반 출력
	//RenderEnemy(_hdc);

	// ** Direction 저장
	//transInfo.Direction = MathManager::GetDirection(oldPosition, transInfo.Position);

	// ** Stage 전장을 벗어났는지 체크
	CheckPositionInBkgBoundary();

	// ** 직전 위치 정보 저장
	//oldPosition = transInfo.Position;	

	// ** 충돌체 갱신은 브릿지에서
	//SetCollider(transInfo);

	return;
}

void Enemy::Render(HDC _hdc)
{
	Super::Render(_hdc);
}

void Enemy::Release()
{
	Super::Release();
}

void Enemy::OnCollision(Object* _pObject)
{
	switch ( _pObject->GetKey() )
	{
		// ** Player와 충돌시 플레이어에 데미지 전달
		case eObjectKey::PLAYER:
			ApplyDamage(_pObject, 1);
			break;
		// ** Player의 총알과 충돌시 Hit이펙트 스폰
		case eObjectKey::BULLET:
			if ( static_cast<Bullet*>(_pObject)->GetOwner()->GetKey() == eObjectKey::PLAYER )
			{
				// ** Hit 이펙트 스폰
				Transform hitEffectTransInfo;
				hitEffectTransInfo.Position = _pObject->GetPosition();
				hitEffectTransInfo.Scale = Vector3(30.0f, 30.0f);
				SpawnManager::SpawnEffect(hitEffectTransInfo, eBridgeKey::EFFECT_HIT);
			}
			break;
		default:
			break;
	}
}

void Enemy::Fire()
{
}

void Enemy::ApplyDamage(Object* _pTarget, int _damage)
{
	// ** ... 데미지를 가할 때의 동작
	switch ( _pTarget->GetKey() )
	{
		case eObjectKey::PLAYER:
			static_cast<Player*>(_pTarget)->TakeDamage(_damage);
			break;
		default:
			break;
	}
}

void Enemy::TakeDamage(int _damage)
{
	HP -= _damage;
	bTakeDamage = true;

	if ( HP <= 0 )
	{
		HP = 0;
		Die();
	}	
}

void Enemy::Die()
{
	// ** bDied flag true 세팅
	bDied = true;

	// ** 폭발 이펙트 스폰
	Transform explosionTransInfo;
	explosionTransInfo.Position = transInfo.Position;
	explosionTransInfo.Scale = transInfo.Scale;
	SpawnManager::SpawnEffect(explosionTransInfo, eBridgeKey::EFFECT_EXPLOSION);
}

void Enemy::CheckPositionInBkgBoundary()
{
	// ** Stage 전장 배경
	Object* pBackground = ObjectManager::GetInstance()->FindObjectWithTag(eObjectKey::BACKGROUND, eTagName::STAGE_MAIN_BKG);

	// ** Stage의 바운더리
	RectF bkgBoundary = pBackground->GetColliderF();

	// ** Stage 바운더리 기준으로 Check 범위를 추가/감소 시킬 Offset
	float Offset = 0.0f;

	// ** 바운더리 크기 조정
	bkgBoundary.Left -= Offset;
	bkgBoundary.Top -= Offset;
	bkgBoundary.Right += Offset;
	bkgBoundary.Bottom += Offset;

	// ** Stage의 바운더리 내 Position이 위치하지 않으면 Destroy
	if ( !CollisionManager::IsPointInRect(bkgBoundary, transInfo.Position) )
	{
		SetStatus(eObjectStatus::DESTROYED);
	}
}