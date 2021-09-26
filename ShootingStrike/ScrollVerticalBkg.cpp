#include "ScrollVerticalBkg.h"
#include "BitmapManager.h"

ScrollVerticalBkg::ScrollVerticalBkg()
	: ScrollDirection(eScrollDirection::DOWN)
	, ImageOffset(0.0f)
	, LoopOffset(0.0f)
	, bLoop(false)
	, bDrawEachStartEnd(false)
{
	Initialize();
}

ScrollVerticalBkg::~ScrollVerticalBkg()
{
	Release();
}

void ScrollVerticalBkg::Initialize()
{
	ScrollDirection = eScrollDirection::DOWN;
	ImageOffset = 0.0f;
	bLoop = true;
	bDrawEachStartEnd = false;
}

void ScrollVerticalBkg::Update()
{
	float ScrollSpeed = pOwner->GetSpeed();
	
	// ** 윗방향 스크롤
	if ( ScrollDirection == eScrollDirection::UP )
	{
		// ** Loop를 위한 이미지 연결 작업중이라면
		if ( bDrawEachStartEnd )
		{
			LoopOffset += ScrollSpeed;

			// ** 이미지 연결 구간이 끝났다면
			if ( LoopOffset > pOwner->GetScale().y )
			{
				ImageOffset = pOwner->GetImage()->GetScale().y - pOwner->GetScale().y;
				bDrawEachStartEnd = false;
			}
		}
		else
		{
			ImageOffset -= ScrollSpeed;

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
			LoopOffset -= ScrollSpeed;

			// ** 이미지 연결 구간이 끝났다면
			if ( LoopOffset < 0.0f )
			{
				ImageOffset = 0.0f;
				bDrawEachStartEnd = false;
			}
		}
		else
		{
			ImageOffset += ScrollSpeed;

			// ** 이미지 최하단에 도달했다면
			if ( ImageOffset > pOwner->GetImage()->GetScale().y - pOwner->GetScale().y )
			{
				// ** 이미지 최하단 Offset으로 고정
				ImageOffset = pOwner->GetImage()->GetScale().y - pOwner->GetScale().y;

				// ** Loop 되어야 하는 상태라면
				if ( bLoop && !bDrawEachStartEnd )
				{
					LoopOffset = pOwner->GetScale().y;
					bDrawEachStartEnd = true;
				}
			}
		}
	}
}

void ScrollVerticalBkg::Render(HDC _hdc)
{
	// ** 이미지 시작과 끝 연결 구간
	// ** Loop Scroll
	if (bLoop && bDrawEachStartEnd )
	{
		TransparentBlt(_hdc,
			(int)(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
			(int)(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
			(int)(pOwner->GetScale().x),
			(int)(LoopOffset),
			pOwner->GetImage()->GetMemDC(),
			(int)(pOwner->GetImage()->GetSegmentationScale().x * pOwner->GetImageOffsetOrder().x),
			(int)(pOwner->GetImage()->GetScale().y - LoopOffset),
			(int)(pOwner->GetImage()->GetSegmentationScale().x),
			(int)(LoopOffset),
			RGB(255, 0, 255));

		TransparentBlt(_hdc,
			(int)(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
			(int)((pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)) + LoopOffset),
			(int)(pOwner->GetScale().x),
			(int)(pOwner->GetScale().y - LoopOffset),
			pOwner->GetImage()->GetMemDC(),
			(int)(pOwner->GetImage()->GetSegmentationScale().x * pOwner->GetImageOffsetOrder().x),
			0,
			(int)(pOwner->GetImage()->GetSegmentationScale().x),
			(int)(pOwner->GetScale().y - LoopOffset),
			RGB(255, 0, 255));
	}
	// ** 일반 Scroll
	else
	{
		TransparentBlt(_hdc,
			(int)(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
			(int)(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
			(int)(pOwner->GetScale().x),
			(int)(pOwner->GetScale().y),
			pOwner->GetImage()->GetMemDC(),
			(int)(pOwner->GetImage()->GetSegmentationScale().x * pOwner->GetImageOffsetOrder().x),
			(int)(ImageOffset),
			(int)(pOwner->GetImage()->GetSegmentationScale().x),
			(int)(pOwner->GetScale().y),
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