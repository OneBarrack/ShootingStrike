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

void BackgroundBridge::Initialize()
{
	if ( pOwner )
	{
		pImage = pOwner->GetImage();
		transInfo = pOwner->GetTransInfo();
		speed = pOwner->GetSpeed();
	}
}

void BackgroundBridge::Update()
{
}

void BackgroundBridge::Render(HDC _hdc)
{
}

void BackgroundBridge::Release()
{
	pOwner = nullptr;
	pImage = nullptr;
}

void BackgroundBridge::ReceiveInfoFromOwner()
{	
	if ( pOwner )
	{
		transInfo = pOwner->GetTransInfo();
		speed = pOwner->GetSpeed();
	}
}

void BackgroundBridge::SendInfoToOwner()
{
	if ( pOwner )
	{
		pOwner->SetTransInfo(transInfo);
		pOwner->SetSpeed(speed);
	}
}