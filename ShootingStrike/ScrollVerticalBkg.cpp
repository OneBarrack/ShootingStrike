#include "ScrollVerticalBkg.h"
#include "BitmapManager.h"

ScrollVerticalBkg::ScrollVerticalBkg()
	: bLoopScroll(false)
	, StageBkgOffset(0.0f)
{
}

ScrollVerticalBkg::~ScrollVerticalBkg()
{
	Release();
}

void ScrollVerticalBkg::Initialize()
{
	bLoopScroll = false;
	StageBkgOffset = 0.0f;
}

void ScrollVerticalBkg::Update()
{
	if ( StageBkgOffset < pOwner->GetScale().y - WindowsHeight )
	{
		StageBkgOffset += pOwner->GetSpeed();
	}
}

void ScrollVerticalBkg::Render(HDC _hdc)
{
	TransparentBlt(_hdc,
		(int)((WindowsWidth * 0.5f) - (pOwner->GetScale().x * 0.5f)),
		(int)0,
		(int)pOwner->GetScale().x,
		(int)WindowsHeight,
		pOwner->GetImage()->GetMemDC(),
		(int)0,
		(int)(pOwner->GetScale().y - WindowsHeight - StageBkgOffset),
		(int)(pOwner->GetScale().x),
		(int)WindowsHeight,
		RGB(255, 0, 255));
}

void ScrollVerticalBkg::Release()
{

}
