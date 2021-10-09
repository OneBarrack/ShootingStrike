#include "BulletBridge.h"

BulletBridge::BulletBridge()
	: pImage(nullptr)
	, transInfo(Transform())
	, speed(0.0f)
{
}

BulletBridge::~BulletBridge()
{
}

void BulletBridge::Initialize()
{
	if ( pOwner )
	{
		pImage = pOwner->GetImage();
		transInfo = pOwner->GetTransInfo();
		speed = pOwner->GetSpeed();
	}
}

void BulletBridge::Update()
{
}

void BulletBridge::Render(HDC _hdc)
{
}

void BulletBridge::Release()
{
	pOwner = nullptr;
	pImage = nullptr;
}

void BulletBridge::ReceiveInfoFromOwner()
{	
	if ( pOwner )
	{
		if ( !pImage )
			pImage = pOwner->GetImage();

		transInfo = pOwner->GetTransInfo();
		speed = pOwner->GetSpeed();
	}
}

void BulletBridge::SendInfoToOwner()
{
	if ( pOwner )
	{
		pOwner->SetTransInfo(transInfo);
		pOwner->SetSpeed(speed);
	}
}