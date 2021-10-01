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

void BulletBridge::ReceiveInfoFromOwner()
{
	pImage = pOwner->GetImage();
	transInfo = pOwner->GetTransInfo();
	speed = pOwner->GetSpeed();
}

void BulletBridge::SendInfoToOwner()
{
	pOwner->SetTransInfo(transInfo);
	pOwner->SetSpeed(speed);
}