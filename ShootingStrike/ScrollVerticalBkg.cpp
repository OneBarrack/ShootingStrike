#include "ScrollVerticalBkg.h"
#include "BitmapManager.h"

ScrollVerticalBkg::ScrollVerticalBkg()
	: ScrollDirection(eScrollDirection::DOWN)
	, ImageOffset(0.0f)
	, LoopOffset(0.0f)
	, bLoop(false)
	, bDrawEachStartEnd(false)
{	
}

ScrollVerticalBkg::~ScrollVerticalBkg()
{
}

void ScrollVerticalBkg::Initialize()
{
	Key = eBridgeKey::BACKGROUND_SCROLL_VERTICAL;
	ScrollDirection = eScrollDirection::DOWN;
	ImageOffset = 0.0f;
	bLoop = true;
	bDrawEachStartEnd = false;
}

void ScrollVerticalBkg::Update()
{
	ReceiveInfoFromOwner();
	
	// ** 윗방향 스크롤
	if ( ScrollDirection == eScrollDirection::UP )
	{
		// ** Loop를 위한 이미지 연결 작업중이라면
		if ( bDrawEachStartEnd )
		{
			LoopOffset += Speed;

			// ** 이미지 연결 구간이 끝났다면
			if ( LoopOffset > TransInfo.Scale.y )
			{
				ImageOffset = pImage->GetScale().y - TransInfo.Scale.y;
				bDrawEachStartEnd = false;
			}
		}
		else
		{
			ImageOffset -= Speed;

			// ** 이미지 최상단에 도달했다면
			if ( ImageOffset < 0.0f )
			{
				// ** 이미지 최상단 Offset으로 고정
				ImageOffset = 0.0f;

				// ** Loop 되어야 하는 상태라면
				if ( bLoop && !bDrawEachStartEnd )
				{					
					LoopOffset = 0.0f;
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
			LoopOffset -= Speed;

			// ** 이미지 연결 구간이 끝났다면
			if ( LoopOffset < 0.0f )
			{
				ImageOffset = 0.0f;
				bDrawEachStartEnd = false;
			}
		}
		else
		{
			ImageOffset += Speed;

			// ** 이미지 최하단에 도달했다면
			if ( ImageOffset > pImage->GetScale().y - TransInfo.Scale.y )
			{
				// ** 이미지 최하단 Offset으로 고정
				ImageOffset = pImage->GetScale().y - TransInfo.Scale.y;

				// ** Loop 되어야 하는 상태라면
				if ( bLoop && !bDrawEachStartEnd )
				{
					LoopOffset = pOwner->GetScale().y;
					bDrawEachStartEnd = true;
				}
			}
		}
	}

	SendInfoToOwner();
}

void ScrollVerticalBkg::Render(HDC _hdc)
{
	if ( !pImage )
		return;

	// ** 이미지 시작과 끝 연결 구간
	// ** Loop Scroll
	if (bLoop && bDrawEachStartEnd )
	{
		TransparentBlt(_hdc,
			(int)(TransInfo.Position.x - (TransInfo.Scale.x * 0.5f)),
			(int)(TransInfo.Position.y - (TransInfo.Scale.y * 0.5f)),
			(int)(TransInfo.Scale.x),
			(int)(LoopOffset),
			pImage->GetMemDC(),
			(int)(pImage->GetSegmentationScale().x * pOwner->GetImageOffsetOrder().x),
			(int)(pImage->GetScale().y - LoopOffset),
			(int)(pImage->GetSegmentationScale().x),
			(int)(LoopOffset),
			RGB(255, 0, 255));

		TransparentBlt(_hdc,
			(int)(TransInfo.Position.x - (TransInfo.Scale.x * 0.5f)),
			(int)((TransInfo.Position.y - (TransInfo.Scale.y * 0.5f)) + LoopOffset),
			(int)(TransInfo.Scale.x),
			(int)(TransInfo.Scale.y - LoopOffset),
			pImage->GetMemDC(),
			(int)(pImage->GetSegmentationScale().x * pOwner->GetImageOffsetOrder().x),
			0,
			(int)(pImage->GetSegmentationScale().x),
			(int)(TransInfo.Scale.y - LoopOffset),
			RGB(255, 0, 255));
	}
	// ** 일반 Scroll
	else
	{
		TransparentBlt(_hdc,
			(int)(TransInfo.Position.x - (TransInfo.Scale.x * 0.5f)),
			(int)(TransInfo.Position.y - (TransInfo.Scale.y * 0.5f)),
			(int)(TransInfo.Scale.x),
			(int)(TransInfo.Scale.y),
			pImage->GetMemDC(),
			(int)(pImage->GetSegmentationScale().x * pOwner->GetImageOffsetOrder().x),
			(int)(ImageOffset),
			(int)(pImage->GetSegmentationScale().x),
			(int)(TransInfo.Scale.y),
			RGB(255, 0, 255));
	}	
}

void ScrollVerticalBkg::Release()
{

}

void ScrollVerticalBkg::StartTop() 
{ 
	ImageOffset = 0.0f;
}

void ScrollVerticalBkg::StartBottom() 
{ 
	ImageOffset = pOwner->GetImage()->GetScale().y - pOwner->GetScale().y;		
}

void ScrollVerticalBkg::ScrollUp() 
{
	ScrollDirection = eScrollDirection::UP; 
}

void ScrollVerticalBkg::ScrollDown() 
{
	ScrollDirection = eScrollDirection::DOWN;
}