#include "EffectBridge.h"

EffectBridge::EffectBridge()
	: pImage(nullptr)
	, segmentImageCount(0)
{
}

EffectBridge::~EffectBridge()
{
}

void EffectBridge::Initialize()
{
	if ( pOwner )
	{
		if ( !pImage )
		{
			pImage = pOwner->GetImage();			
			segmentImageCount = static_cast<int>(pImage->GetScale().x / pImage->GetSegmentationScale().x);
		}		
	}
}

void EffectBridge::Update()
{
}

void EffectBridge::Render(HDC _hdc)
{	
}

void EffectBridge::Release()
{
	pOwner = nullptr;
	pImage = nullptr;
}

void EffectBridge::ReceiveInfoFromOwner()
{
	if ( pOwner )
	{
		if ( !pImage )
		{
			pImage = pOwner->GetImage();			
			segmentImageCount = static_cast<int>(pImage->GetScale().x / pImage->GetSegmentationScale().x);
		}		
	}
}

void EffectBridge::SendInfoToOwner()
{
}
