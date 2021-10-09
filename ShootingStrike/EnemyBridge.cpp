#include "EnemyBridge.h"

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
	}
}

void EnemyBridge::SendInfoToOwner()
{
	if ( pOwner )
	{
		pOwner->SetTransInfo(transInfo);
		pOwner->SetCollider(collider);
		pOwner->SetSpeed(speed);
	}
}