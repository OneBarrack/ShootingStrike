#include "BackgroundBridge.h"

BackgroundBridge::BackgroundBridge()
	: pImage(nullptr)
	, TransInfo(Transform())
	, Speed(0.0f)
{
}

BackgroundBridge::~BackgroundBridge()
{
}

void BackgroundBridge::ReceiveInfoFromOwner()
{
	pImage = pOwner->GetImage();
	TransInfo = pOwner->GetTransInfo();
	Speed = pOwner->GetSpeed();
}

void BackgroundBridge::SendInfoToOwner()
{
	pOwner->SetTransInfo(TransInfo);
	pOwner->SetSpeed(Speed);
}