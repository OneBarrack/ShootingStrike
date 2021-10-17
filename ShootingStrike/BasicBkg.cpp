#include "BasicBkg.h"
#include "BitmapManager.h"

BasicBkg::BasicBkg()
	: bPlayAnimation(false)
	, segmentationIndex(0)
	, time(0)
	, animationDelay(0)
{
}

BasicBkg::~BasicBkg()
{

}

void BasicBkg::Initialize()
{
	Super::Initialize();

	key = eBridgeKey::BACKGROUND_BASIC;

	bPlayAnimation = false;
	segmentationIndex = 0;
	time = GetTickCount64();
	int animationDelay = 100;
}

void BasicBkg::Update()
{
	Super::Update();

	ReceiveInfoFromOwner();

	SendInfoToOwner();
}

void BasicBkg::Render(HDC _hdc)
{
	Super::Render(_hdc);

	if ( !pImage )
		return;

	if ( bPlayAnimation )
	{		
		if ( time + animationDelay < GetTickCount64() )
		{			
			time = GetTickCount64();

			int maxSegmentationIndex = static_cast<int>(pImage->GetScale().x / pImage->GetSegmentationScale().x);
			if ( segmentationIndex == maxSegmentationIndex )
				segmentationIndex = 0;

			TransparentBlt(_hdc,
				(int)(transInfo.Position.x - (transInfo.Scale.x * 0.5f)),
				(int)(transInfo.Position.y - (transInfo.Scale.y * 0.5f)),
				(int)(transInfo.Scale.x),
				(int)(transInfo.Scale.y),
				pImage->GetMemDC(),
				(int)(pImage->GetSegmentationScale().x * segmentationIndex),
				0,
				(int)(pImage->GetSegmentationScale().x),
				(int)(pImage->GetSegmentationScale().y),
				RGB(255, 0, 255));

			++segmentationIndex;
		}
	}
	else
	{
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
}

void BasicBkg::Release()
{	
	Super::Release();
}
