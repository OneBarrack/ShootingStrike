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
	Key = eBridgeKey::BACKGROUND_BASIC;
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
		(int)(TransInfo.Position.x - (TransInfo.Scale.x * 0.5f)),
		(int)(TransInfo.Position.y - (TransInfo.Scale.y * 0.5f)),
		(int)(TransInfo.Scale.x),
		(int)(TransInfo.Scale.y),
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
