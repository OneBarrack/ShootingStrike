#include "UIBridge.h"

UIBridge::UIBridge()
	: pImage(nullptr)
{
}

UIBridge::~UIBridge()
{
}

void UIBridge::Initialize()
{
	if ( pOwner )
	{
		pImage = pOwner->GetImage();
	}
}

void UIBridge::Update()
{
}

void UIBridge::Render(HDC _hdc)
{
}

void UIBridge::Release()
{
	pOwner = nullptr;
	pImage = nullptr;
}

void UIBridge::ReceiveInfoFromOwner()
{	
}

void UIBridge::SendInfoToOwner()
{
}