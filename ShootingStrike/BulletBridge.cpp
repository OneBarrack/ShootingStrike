#include "BulletBridge.h"

BulletBridge::BulletBridge()
	: TransInfo(Transform())
	, Speed(0.0f)
{
}

BulletBridge::~BulletBridge()
{
}

void BulletBridge::ReceiveInfo()
{
	TransInfo = pOwner->GetTransInfo();
	Speed = pOwner->GetSpeed();
}

void BulletBridge::SendInfo()
{
	pOwner->SetTransInfo(TransInfo);
	pOwner->SetSpeed(Speed);
}