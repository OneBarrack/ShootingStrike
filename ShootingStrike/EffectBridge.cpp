#include "EffectBridge.h"

EffectBridge::EffectBridge()
	: pImage(nullptr)
{
}

EffectBridge::~EffectBridge()
{
}

void EffectBridge::Initialize()
{
	if ( pOwner )
	{
		pImage = pOwner->GetImage();
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
}

void EffectBridge::SendInfoToOwner()
{
}
