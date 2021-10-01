#include "BasicBkg.h"
#include "BitmapManager.h"

BasicBkg::BasicBkg()
{
}

BasicBkg::~BasicBkg()
{

}

void BasicBkg::Initialize()
{
	key = eBridgeKey::BACKGROUND_BASIC;
}

void BasicBkg::Update()
{
	ReceiveInfoFromOwner();
	SendInfoToOwner();
}

void BasicBkg::Render(HDC _hdc)
{
	if ( !pImage )
		return;

	TransparentBlt(_hdc,
		(int)(transInfo.Position.x - (transInfo.Scale.x * 0.5f)),
		(int)(transInfo.Position.y - (transInfo.Scale.y * 0.5f)),
		(int)(transInfo.Scale.x),
		(int)(transInfo.Scale.y),
		pImage->GetMemDC(),
		(int)(pImage->GetSegmentationScale().x * pOwner->GetImageOffsetOrder().x),
		(int)(pImage->GetSegmentationScale().y * pOwner->GetImageOffsetOrder().y),
		(int)(pImage->GetSegmentationScale().x),
		(int)(pImage->GetSegmentationScale().y),
		RGB(255, 0, 255));
}

void BasicBkg::Release()
{

}
