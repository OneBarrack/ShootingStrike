#include "EnemyBridge.h"
#include "Enemy.h"
#include "MathManager.h"

EnemyBridge::EnemyBridge()
	: pImage(nullptr)
	, transInfo(Transform())
	, speed(0.0f)
	, fireBulletIntervalTime(0)
	, destPosition(Vector3())
	, bChangedDestPos(false)
	, bStopAtDest(false)
	, bArrivedToDest(false)
	, isSpawing(false)
{
}

EnemyBridge::~EnemyBridge()
{
}

void EnemyBridge::Initialize()
{
	if ( pOwner )
	{
		pImage = pOwner->GetImage();
		transInfo = pOwner->GetTransInfo();
		speed = pOwner->GetSpeed();
		acceleration = pOwner->GetAcceleration();
		destPosition = static_cast<Enemy*>(pOwner)->GetDestPosition();
		bChangedDestPos = static_cast<Enemy*>(pOwner)->GetChangedDestPos();
		bStopAtDest = static_cast<Enemy*>(pOwner)->GetStopAtDest();
		bArrivedToDest = static_cast<Enemy*>(pOwner)->GetArrivedToDest();
		isSpawing = static_cast<Enemy*>(pOwner)->IsSpawning();
	}

	bulletScript.Initialize();
}

void EnemyBridge::Update()
{
	// ** 가속도 적용
	speed += acceleration;

	// ** 목적지 변경시 Direction 변경
	if ( bChangedDestPos )
	{
		transInfo.Direction = MathManager::GetDirection(transInfo.Position, destPosition);
		bChangedDestPos = false;
		bArrivedToDest = false;
	}

	// ** 목적지 도착 전이라면 목적지까지 거리 체크
	if ( !bArrivedToDest )
	{
		// ** 다음 프레임에 목적지를 넘어가는 상태라면
		if ( abs(destPosition.x - transInfo.Position.x) <= abs(transInfo.Direction.x * speed) &&
			abs(destPosition.y - transInfo.Position.y) <= abs(transInfo.Direction.y * speed) )
		{
			// ** 목적지 도달
			transInfo.Position = destPosition;
			bArrivedToDest = true;
		}
	}
}

void EnemyBridge::Render(HDC _hdc)
{
}

void EnemyBridge::Release()
{
	pOwner = nullptr;
	pImage = nullptr;
}

void EnemyBridge::ReceiveInfoFromOwner()
{
	if ( pOwner )
	{
		if ( !pImage )
			pImage = pOwner->GetImage();

		transInfo = pOwner->GetTransInfo();
		collider = pOwner->GetCollider();
		speed = pOwner->GetSpeed();
		acceleration = pOwner->GetAcceleration();
		fireBulletIntervalTime = static_cast<Enemy*>(pOwner)->GetFireBulletIntervalTime();
		destPosition = static_cast<Enemy*>(pOwner)->GetDestPosition();
		bChangedDestPos = static_cast<Enemy*>(pOwner)->GetChangedDestPos();
		bStopAtDest = static_cast<Enemy*>(pOwner)->GetStopAtDest();
		bArrivedToDest = static_cast<Enemy*>(pOwner)->GetArrivedToDest();
		isSpawing = static_cast<Enemy*>(pOwner)->IsSpawning();
	}
}

void EnemyBridge::SendInfoToOwner()
{
	if ( pOwner )
	{
		pOwner->SetTransInfo(transInfo);
		pOwner->SetCollider(collider);
		pOwner->SetSpeed(speed);
		pOwner->SetAcceleration(acceleration);
		static_cast<Enemy*>(pOwner)->SetFireBulletIntervalTime(fireBulletIntervalTime);
		static_cast<Enemy*>(pOwner)->SetDestPosition(destPosition);
		static_cast<Enemy*>(pOwner)->SetChangedDestPos(bChangedDestPos);
		static_cast<Enemy*>(pOwner)->SetStopAtDest(bStopAtDest);
		static_cast<Enemy*>(pOwner)->SetArrivedToDest(bArrivedToDest);
		static_cast<Enemy*>(pOwner)->SetSpawnStatus(isSpawing);
	}
}