#include "Enemy.h"
#include "Bridge.h"
#include "Player.h"
#include "BitmapManager.h"
#include "MathManager.h"

Enemy::Enemy()
	: HP(0)
	, bSpawing(false)
	, bAttacking(false)
	, bTakeDamage(false)
	, bDied(false)
	, HitPoint(0)
	, DeathPoint(0)
	, Frame(0)
	, OldPosition(Vector3())
{

}

Enemy::~Enemy()
{
	Release();
}

void Enemy::Initialize()
{
	Super::Initialize();

	Key = eObjectKey::ENEMY;
	Status = eObjectStatus::ACTIVATED;
	CollisionType = eCollisionType::RECT;
	OldPosition = TransInfo.Position;
	bGenerateCollisionEvent = true;

	HP = 5;

	bSpawing = false;
	bAttacking = false;
	bTakeDamage = false;
	bDied = false;

	Speed = 3.0f;
	Frame = 0;
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
	TransInfo.Direction = MathManager::GetDirection(OldPosition, TransInfo.Position);

	// ** 직전 위치 정보 저장
	OldPosition = TransInfo.Position;

	// ** 충돌체 갱신
	Collider = TransInfo;

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

void Enemy::ApplyDamage(Object* _pTarget, int _Damage)
{
	// ** ... 데미지를 가할 때의 동작
	switch ( _pTarget->GetKey() )
	{
		case eObjectKey::PLAYER:
			static_cast<Player*>(_pTarget)->TakeDamage(_Damage);
			break;
	}
}

void Enemy::TakeDamage(int _Damage)
{
	HP -= _Damage;
	bTakeDamage = true;

	if ( HP <= 0 )
	{
		HP = 0;
		bDied = true;
	}
}