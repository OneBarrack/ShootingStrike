#include "StayInPlaceItem.h"

StayInPlaceItem::StayInPlaceItem()
{

}

StayInPlaceItem::~StayInPlaceItem()
{
}


void StayInPlaceItem::Initialize()
{
	Super::Initialize();
	 
	key = eBridgeKey::ITEM_STAY_IN_PLACE;
}

void StayInPlaceItem::Update()
{
	Super::Update();

	ReceiveInfoFromOwner();

	SendInfoToOwner();
}

void StayInPlaceItem::Render(HDC _hdc)
{
	Super::Render(_hdc);

	if ( !pImage )
		return;

	//TransparentBlt(_hdc, // ** 최종 출력 위치
	//	int((pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)) + ((->GetSegmentationScale().x + 15) * offset)),
	//	int(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
	//	int(pNumberImage->GetSegmentationScale().x + 13),
	//	int(pOwner->GetScale().y),
	//	pNumberImage->GetMemDC(),
	//	int(pNumberImage->GetSegmentationScale().x * Num),
	//	0,
	//	int(pNumberImage->GetSegmentationScale().x),
	//	int(pNumberImage->GetScale().y),
	//	RGB(255, 0, 255));
}

void StayInPlaceItem::Release()
{
	Super::Release();
}