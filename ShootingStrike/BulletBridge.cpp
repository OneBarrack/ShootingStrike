#include "BulletBridge.h"

BulletBridge::BulletBridge()
	: pImage(nullptr)
	, TransInfo(Transform())
	, Speed(0.0f)
{
}

BulletBridge::~BulletBridge()
{
}

void BulletBridge::ReceiveInfoFromOwner()
{
	pImage = pOwner->GetImage();
	TransInfo = pOwner->GetTransInfo();
	Speed = pOwner->GetSpeed();
}

void BulletBridge::SendInfoToOwner()
{
	pOwner->SetTransInfo(TransInfo);
	pOwner->SetSpeed(Speed);
}