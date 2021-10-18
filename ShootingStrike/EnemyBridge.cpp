#include "EnemyBridge.h"
#include "Enemy.h"
#include "MathManager.h"

EnemyBridge::EnemyBridge()
	: pImage(nullptr)
	, transInfo(Transform())
	, speed(0.0f)
	, fireBulletIntervalTime(0)
	, destPosition(Vector3())
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
		isSpawing = static_cast<Enemy*>(pOwner)->IsSpawning();
	}

	bulletScript.Initialize();
}

void EnemyBridge::Update()
{
	// ** 가속도 적용
	speed += acceleration;

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
		static_cast<Enemy*>(pOwner)->SetSpawnStatus(isSpawing);
	}
}