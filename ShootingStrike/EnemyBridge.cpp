#include "EnemyBridge.h"
#include "MathManager.h"

EnemyBridge::EnemyBridge()
	: pImage(nullptr)
	, transInfo(Transform())
	, speed(0.0f)
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
	}

	bulletScript.Initialize();
}

void EnemyBridge::Update()
{
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
	}
}

void EnemyBridge::SendInfoToOwner()
{
	if ( pOwner )
	{
		transInfo.Direction = MathManager::GetDirection(pOwner->GetTransInfo().Position, transInfo.Position);
		pOwner->SetTransInfo(transInfo);
		pOwner->SetCollider(collider);
		pOwner->SetSpeed(speed);
		pOwner->SetAcceleration(acceleration);
	}
}