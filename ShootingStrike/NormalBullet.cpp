#include "NormalBullet.h"
#include "Object.h"
#include "BitmapManager.h"

NormalBullet::NormalBullet() 
{
}

NormalBullet::~NormalBullet()
{
}


void NormalBullet::Initialize()
{
	Key = eBridgeKey::BULLET_NORMAL;
}

void NormalBullet::Update()
{
	// ** Owner의 데이터를 받아옴
	ReceiveInfoFromOwner();

	TransInfo.Position.x += TransInfo.Direction.x * Speed;
	TransInfo.Position.y += TransInfo.Direction.y * Speed;

	// ** Owner로 가공된 데이터 전달
	SendInfoToOwner();
}


void NormalBullet::Render(HDC _hdc)
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

void NormalBullet::Release()
{

}
