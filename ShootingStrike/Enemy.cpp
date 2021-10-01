#include "Enemy.h"
#include "Bridge.h"
#include "Player.h"
#include "BitmapManager.h"
#include "MathManager.h"
#include "ObjectManager.h"
#include "CollisionManager.h"

Enemy::Enemy()
	: HP(0)
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

	HP = 5;

	bSpawing = false;
	bAttacking = false;
	bTakeDamage = false;
	bDied = false;

	speed = 3.0f;
}

void Enemy::Update()
{
	Super::Update();

	// ** 스폰 중
	if ( bSpawing )
	{
		// SpawnEnemy
		return;
	}

	// ** 죽음
	if ( bDied )
	{
		bDied = false;
		//return;
	}

	// ** 피해를 입었을 시
	if ( bTakeDamage )
	{

	}

	// ** 일반 출력
	//RenderEnemy(_hdc);

	// ** Direction 저장
	transInfo.Direction = MathManager::GetDirection(oldPosition, transInfo.Position);

	// ** Stage 전장을 벗어났는지 체크
	CheckPositionInBkgBoundary();

	// ** 직전 위치 정보 저장
	oldPosition = transInfo.Position;

	// ** 충돌체 갱신
	SetCollider(transInfo);

	return;
}

void Enemy::Render(HDC _hdc)
{
	Super::Render(_hdc);

	//TransparentBlt(_hdc, // ** 최종 출력 위치
	//	int(TransInfo.Position.x - (TransInfo.Scale.x * 0.5f)),
	//	int(TransInfo.Position.y + (TransInfo.Scale.x * 0.5f) - Offset.y - 50),
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
	Super::Release();
}

void Enemy::OnCollision(Object* _pObject)
{
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
		bDied = true;
	}
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