#include "BackgroundBridge.h"

BackgroundBridge::BackgroundBridge()
	: pImage(nullptr)
	, transInfo(Transform())
	, speed(0.0f)
{
}

BackgroundBridge::~BackgroundBridge()
{
}

void BackgroundBridge::ReceiveInfoFromOwner()
{
	pImage = pOwner->GetImage();
	transInfo = pOwner->GetTransInfo();
	speed = pOwner->GetSpeed();
}

void BackgroundBridge::SendInfoToOwner()
{
	pOwner->SetTransInfo(transInfo);
	pOwner->SetSpeed(speed);
}