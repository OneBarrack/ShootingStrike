#include "BasicBkg.h"
#include "BitmapManager.h"

BasicBkg::BasicBkg()
{
	Initialize();
}

BasicBkg::~BasicBkg()
{
	Release();
}

void BasicBkg::Initialize()
{
	Key = eBridgeKey::BACKGROUND_BASIC;
}

void BasicBkg::Update()
{

}

void BasicBkg::Render(HDC _hdc)
{
	Bitmap* pImage = pOwner->GetImage();
	if ( !pImage )
		return;

	TransparentBlt(_hdc,
		(int)(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
		(int)(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
		(int)(pOwner->GetScale().x),
		(int)(pOwner->GetScale().y),
		pOwner->GetImage()->GetMemDC(),
		(int)(pImage->GetSegmentationScale().x * pOwner->GetImageOffsetOrder().x),
		(int)(pImage->GetSegmentationScale().y * pOwner->GetImageOffsetOrder().y),
		(int)(pImage->GetSegmentationScale().x),
		(int)(pImage->GetSegmentationScale().y),
		RGB(255, 0, 255));
}

void BasicBkg::Release()
{

}
