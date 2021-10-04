#include "ScrollVerticalBkg.h"
#include "BitmapManager.h"

ScrollVerticalBkg::ScrollVerticalBkg()
	: scrollDirection(eScrollDirection::DOWN)
	, imageOffset(0.0f)
	, imageOffsetForRestart(0.0f)
	, bLoop(false)
	, bDrawEachStartEnd(false)
{	
}

ScrollVerticalBkg::~ScrollVerticalBkg()
{
}

void ScrollVerticalBkg::Initialize()
{
	Super::Initialize();

	key = eBridgeKey::BACKGROUND_SCROLL_VERTICAL;
	scrollDirection = eScrollDirection::DOWN;
	imageOffset = 0.0f;
	bLoop = true;
	bDrawEachStartEnd = false;
}

void ScrollVerticalBkg::Update()
{
	Super::Update();

	ReceiveInfoFromOwner();
	
	// ** 윗방향 스크롤
	if ( scrollDirection == eScrollDirection::UP )
	{
		// ** Loop를 위한 이미지 연결 작업중이라면
		if ( bDrawEachStartEnd )
		{
			imageOffsetForRestart += speed;

			// ** 이미지 연결 구간이 끝났다면
			if ( imageOffsetForRestart > transInfo.Scale.y )
			{
				imageOffset = pImage->GetScale().y - transInfo.Scale.y;
				bDrawEachStartEnd = false;
			}
		}
		else
		{
			imageOffset -= speed;

			// ** 이미지 최상단에 도달했다면
			if ( imageOffset < 0.0f )
			{
				// ** 이미지 최상단 Offset으로 고정
				imageOffset = 0.0f;

				// ** Loop 되어야 하는 상태라면
				if ( bLoop && !bDrawEachStartEnd )
				{					
					imageOffsetForRestart = 0.0f;
					bDrawEachStartEnd = true;
				}
			}
		}
	}
	// ** 아랫방향 스크롤 Direction == eScrollDirection::DOWN
	else 
	{
		// ** Loop를 위한 이미지 연결 작업중인지
		if ( bDrawEachStartEnd )
		{
			imageOffsetForRestart -= speed;

			// ** 이미지 연결 구간이 끝났다면
			if ( imageOffsetForRestart < 0.0f )
			{
				imageOffset = 0.0f;
				bDrawEachStartEnd = false;
			}
		}
		else
		{
			imageOffset += speed;

			// ** 이미지 최하단에 도달했다면
			if ( imageOffset > pImage->GetScale().y - transInfo.Scale.y )
			{
				// ** 이미지 최하단 Offset으로 고정
				imageOffset = pImage->GetScale().y - transInfo.Scale.y;

				// ** Loop 되어야 하는 상태라면
				if ( bLoop && !bDrawEachStartEnd )
				{
					imageOffsetForRestart = pOwner->GetScale().y;
					bDrawEachStartEnd = true;
				}
			}
		}
	}

	SendInfoToOwner();
}

void ScrollVerticalBkg::Render(HDC _hdc)
{
	Super::Render(_hdc);

	if ( !pImage )
		return;

	// ** 이미지 시작과 끝 연결 구간
	// ** Loop Scroll
	if (bLoop && bDrawEachStartEnd )
	{
		TransparentBlt(_hdc,
			(int)(transInfo.Position.x - (transInfo.Scale.x * 0.5f)),
			(int)(transInfo.Position.y - (transInfo.Scale.y * 0.5f)),
			(int)(transInfo.Scale.x),
			(int)(imageOffsetForRestart),
			pImage->GetMemDC(),
			(int)(pImage->GetSegmentationScale().x * pOwner->GetImageOffsetOrder().x),
			(int)(pImage->GetScale().y - imageOffsetForRestart),
			(int)(pImage->GetSegmentationScale().x),
			(int)(imageOffsetForRestart),
			RGB(255, 0, 255));

		TransparentBlt(_hdc,
			(int)(transInfo.Position.x - (transInfo.Scale.x * 0.5f)),
			(int)((transInfo.Position.y - (transInfo.Scale.y * 0.5f)) + imageOffsetForRestart),
			(int)(transInfo.Scale.x),
			(int)(transInfo.Scale.y - imageOffsetForRestart),
			pImage->GetMemDC(),
			(int)(pImage->GetSegmentationScale().x * pOwner->GetImageOffsetOrder().x),
			0,
			(int)(pImage->GetSegmentationScale().x),
			(int)(transInfo.Scale.y - imageOffsetForRestart),
			RGB(255, 0, 255));
	}
	// ** 일반 Scroll
	else
	{
		TransparentBlt(_hdc,
			(int)(transInfo.Position.x - (transInfo.Scale.x * 0.5f)),
			(int)(transInfo.Position.y - (transInfo.Scale.y * 0.5f)),
			(int)(transInfo.Scale.x),
			(int)(transInfo.Scale.y),
			pImage->GetMemDC(),
			(int)(pImage->GetSegmentationScale().x * pOwner->GetImageOffsetOrder().x),
			(int)(imageOffset),
			(int)(pImage->GetSegmentationScale().x),
			(int)(transInfo.Scale.y),
			RGB(255, 0, 255));
	}	
}

void ScrollVerticalBkg::Release()
{
	Super::Release();
}

void ScrollVerticalBkg::StartTop() 
{ 
	imageOffset = 0.0f;
}

void ScrollVerticalBkg::StartBottom() 
{ 
	imageOffset = pOwner->GetImage()->GetScale().y - pOwner->GetScale().y;		
}

void ScrollVerticalBkg::ScrollUp() 
{
	scrollDirection = eScrollDirection::UP; 
}

void ScrollVerticalBkg::ScrollDown() 
{
	scrollDirection = eScrollDirection::DOWN;
}