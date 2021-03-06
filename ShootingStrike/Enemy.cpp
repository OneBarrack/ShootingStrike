#include "Enemy.h"
#include "Bridge.h"
#include "Player.h"
#include "Bullet.h"
#include "SoundManager.h"
#include "BitmapManager.h"
#include "MathManager.h"
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "SpawnManager.h"
#include "InputManager.h"
#include "BounceOnWallItem.h"
#include "Item.h"

Enemy::Enemy()
	: enemyType(eEnemyType::ENEMY_BLUE_ELF)
	, dropItemType(eItemType::NONE)
	, maxHP(0)
	, HP(0)
	, isSpawing(false)
	, isAttacking(false)
	, isTakeDamage(false)
	, isDied(false)
	, hitScore(0)
	, deathScore(0)
	, oldPosition(Vector3())
	, fireBulletIntervalTime(0)
	, moveState(eMoveState::READY)
	, totalDegreeForSpin(0.0f)
{

}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	Super::Initialize();

	objectKey = eObjectKey::ENEMY;
	objectStatus = eObjectStatus::ACTIVATED;
	collisionType = eCollisionType::RECT;
	oldPosition = transInfo.Position;
	bGenerateCollisionEvent = true;

	enemyType = eEnemyType::NONE;
	dropItemType = eItemType::NONE;
	maxHP = 1;
	HP = 1;

	isSpawing = false;
	isAttacking = false;
	isTakeDamage = false;
	isDied = false;

	hitScore = 10;
	deathScore = 100;

	speed = 3.0f;
	fireBulletIntervalTime = 0;
	destPosition = Vector3();
	moveState = eMoveState::READY;
	totalDegreeForSpin = 0.0f;

	InitMoveInfo();
}

void Enemy::Update()
{
	Super::Update();

	speed += acceleration;

	if ( !moveInfos.empty() )
	{
		eMoveType moveType = moveInfos.front().first;
		destPosition = moveInfos.front().second;

		bool bLoop = false;

		// **Ready 단계. 초기화 작업
		if ( moveState == eMoveState::READY )
		{
			moveState = eMoveState::MOVING;
			
			switch ( moveType )
			{
				case eMoveType::MOVE_TO:
					transInfo.Direction = MathManager::GetDirection(transInfo.Position, destPosition);
					break;
				case eMoveType::SPIN_LEFT:
					totalDegreeForSpin = 0.0f;
					break;
				case eMoveType::SPIN_RIGHT:
					totalDegreeForSpin = 0.0f;
					break;
				case eMoveType::BACK_AND_FORTH_LEFT:
					break;
				case eMoveType::BACK_AND_FORTH_RIGHT:
					break;
			}
		}

		// ** Moving 단계. Move 진행
		switch ( moveType )
		{
			case eMoveType::MOVE_TO:
				break;
			case eMoveType::SPIN_LEFT_FOR_LOOP:
				bLoop = true;
				[[fallthrough]];
			case eMoveType::SPIN_LEFT:
			{
				float rotationDegree = -1.0f;
				totalDegreeForSpin += rotationDegree;

				if ( !bLoop && abs(totalDegreeForSpin) >= 360 )
				{
					moveState = eMoveState::END;
				}

				transInfo.Direction = MathManager::RotateByDegree(transInfo.Direction, rotationDegree);				
				break;
			}			
			case eMoveType::SPIN_RIGHT_FOR_LOOP:
				bLoop = true;
				[[fallthrough]];
			case eMoveType::SPIN_RIGHT:
			{
				float rotationDegree = 1.0f;
				totalDegreeForSpin += rotationDegree;

				if ( !bLoop && abs(totalDegreeForSpin) >= 360 )
				{
					moveState = eMoveState::END;
				}

				transInfo.Direction = MathManager::RotateByDegree(transInfo.Direction, rotationDegree);				
				break;
			}
			case eMoveType::BACK_AND_FORTH_LEFT:
			{
				float backAndForthDegree = 1.0f;

				// ** 수직 벡터를 구한다.
				Vector3 perpendicularDirection;
				perpendicularDirection.x = transInfo.Direction.y;
				perpendicularDirection.y = -transInfo.Direction.x;

				transInfo.Position.x += perpendicularDirection.x * (speed * 2) * sinf(MathManager::DegreeToRadian(totalDegreeForSpin));
				transInfo.Position.y += perpendicularDirection.y * (speed * 2) * sinf(MathManager::DegreeToRadian(totalDegreeForSpin));

				totalDegreeForSpin += backAndForthDegree;
				break;
			}
			case eMoveType::BACK_AND_FORTH_RIGHT:
				float backAndForthDegree = 1.0f;

				// ** 수직 벡터를 구한다.
				Vector3 perpendicularDirection;
				perpendicularDirection.x = -transInfo.Direction.y;
				perpendicularDirection.y = transInfo.Direction.x;

				transInfo.Position.x += perpendicularDirection.x * (speed * 2) * sinf(MathManager::DegreeToRadian(totalDegreeForSpin));
				transInfo.Position.y += perpendicularDirection.y * (speed * 2) * sinf(MathManager::DegreeToRadian(totalDegreeForSpin));

				totalDegreeForSpin += backAndForthDegree;
				break;
		}

		transInfo.Position.x += transInfo.Direction.x * speed;
		transInfo.Position.y += transInfo.Direction.y * speed;

		// ** 다음 프레임에 목적지를 넘어가는 상태라면
		if ( abs(destPosition.x - transInfo.Position.x) <= abs(transInfo.Direction.x * speed) &&
			abs(destPosition.y - transInfo.Position.y) <= abs(transInfo.Direction.y * speed) )
		{
			// ** 목적지 도달
			transInfo.Position = destPosition;
			moveState = eMoveState::END;
		}

		if ( moveState == eMoveState::END )
		{
			moveInfos.pop();
			moveState = eMoveState::READY;
		}
	}	

	// ** Stage 전장을 벗어났는지 체크
	CheckPositionInBkgBoundary();

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
		// ** Player와 충돌시 
		case eObjectKey::PLAYER:
			// ** 플레이어가 무적상태가 아니라면 데미지 전달
			if ( static_cast<Player*>(_pObject)->IsInvicible() == false )
			{
				ApplyDamage(_pObject, 1);
			}
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
	isTakeDamage = true;

	if ( !isDied && HP <= 0 )
	{
		HP = 0;
		Die();
	}	
}

void Enemy::Spawn()
{
	isSpawing = true;
	objectStatus = eObjectStatus::ACTIVATED;
}

void Enemy::Die()
{
	// ** Play explosion sound
	SoundManager::GetInstance()->Play(eSoundKey::EFFECT_EXPLOSION);

	// ** bDied flag true 세팅
	isDied = true;

	// ** 폭발 이펙트 스폰
	Transform explosionTransInfo;
	explosionTransInfo.Position = transInfo.Position;
	explosionTransInfo.Scale = transInfo.Scale;
	SpawnManager::SpawnEffect(explosionTransInfo, eBridgeKey::EFFECT_EXPLOSION);	

	// ** 아이템 스폰
	if ( dropItemType != eItemType::NONE )
	{		
		Bridge* pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ITEM_BOUNCE_ON_WALL);
		Object* pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ITEM);
		pObject->SetPosition(transInfo.Position);
		pObject->SetScale(Vector3(40.0f, 40.0f));
		pObject->SetSpeed(2.0f);
		pObject->SetBridge(pBridge);
		static_cast<Item*>(pObject)->SetItemType(dropItemType);
	}

	objectStatus = eObjectStatus::DESTROYED;
}

void Enemy::InitMoveInfo()
{
	moveInfos = queue<pair<eMoveType, Vector3>>();
	moveState = eMoveState::READY;
}

bool Enemy::isMoving()
{
	if ( moveState == eMoveState::MOVING )
		return true;

	return false;
}

void Enemy::SetEnemyType(eEnemyType _enemyType)
{
	enemyType = _enemyType;

	switch ( enemyType )
	{
		case eEnemyType::ENEMY_BLUE_ELF:
			SetMaxHP(15);
			SetHP(15);
			SetHitPoint(10);
			SetDeathPoint(100);
			break;
		case eEnemyType::ENEMY_RED_ELF:
			SetMaxHP(10);
			SetHP(10);
			SetHitPoint(20);
			SetDeathPoint(200);
			break;
		case eEnemyType::ENEMY_GREEN_ELF:
			SetMaxHP(20);
			SetHP(20);
			SetHitPoint(30);
			SetDeathPoint(300);
			break;
		case eEnemyType::ENEMY_WHITE_ELF:
			SetMaxHP(30);
			SetHP(30);
			SetHitPoint(50);
			SetDeathPoint(500);
			break;
		case eEnemyType::ENEMY_MIDDLE_BOSS:
			SetMaxHP(500);
			SetHP(500);
			SetHitPoint(100);
			SetDeathPoint(100000);
			break;
		case eEnemyType::ENEMY_BOSS_ANGEL:
			SetMaxHP(1500);
			SetHP(1500);
			SetHitPoint(256);
			SetDeathPoint(777777);
			break;
		default:
			SetMaxHP(0);
			SetHP(0);
			SetHitPoint(0);
			SetDeathPoint(0);
			break;
	}
}

void Enemy::MoveTo(Vector3 _destPosition)
{
	moveInfos.push(make_pair(eMoveType::MOVE_TO, _destPosition));
}

void Enemy::SpinLeft(bool _bLoop)
{
	// ** Loop 체크
	if ( _bLoop )
		moveInfos.push(make_pair(eMoveType::SPIN_LEFT_FOR_LOOP, Vector3()));
	else
		moveInfos.push(make_pair(eMoveType::SPIN_LEFT, Vector3()));
}

void Enemy::SpinRight(bool _bLoop)
{
	// ** Loop 체크
	if ( _bLoop )
		moveInfos.push(make_pair(eMoveType::SPIN_RIGHT_FOR_LOOP, Vector3()));
	else
		moveInfos.push(make_pair(eMoveType::SPIN_RIGHT, Vector3()));
}

void Enemy::BackAndForthLeft(Vector3 _destPosition)
{
	moveInfos.push(make_pair(eMoveType::BACK_AND_FORTH_LEFT, _destPosition));
}
void Enemy::BackAndForthRight(Vector3 _destPosition)
{
	moveInfos.push(make_pair(eMoveType::BACK_AND_FORTH_RIGHT, _destPosition));
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