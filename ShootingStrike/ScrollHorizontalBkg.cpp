#include "ScrollHorizontalBkg.h"
#include "BitmapManager.h"

ScrollHorizontalBkg::ScrollHorizontalBkg()
	: ScrollDirection(eScrollDirection::LEFT)
	, ImageOffset(0.0f)
	, LoopOffset(0.0f)
	, bLoop(false)
	, bDrawEachStartEnd(false)
{
	Initialize();
}

ScrollHorizontalBkg::~ScrollHorizontalBkg()
{
	Release();
}

void ScrollHorizontalBkg::Initialize()
{
	Key = eBridgeKey::BACKGROUND_SCROLL_HORIZONTAL;
	ScrollDirection = eScrollDirection::LEFT;
	ImageOffset = 0.0f;
	bLoop = true;
	bDrawEachStartEnd = false;
}

void ScrollHorizontalBkg::Update()
{
	float ScrollSpeed = pOwner->GetSpeed();

	// ** 윗방향 스크롤
	if ( ScrollDirection == eScrollDirection::LEFT )
	{
		// ** Loop를 위한 이미지 연결 작업중이라면
		if ( bDrawEachStartEnd )
		{
			LoopOffset += ScrollSpeed;

			// ** 이미지 연결 구간이 끝났다면
			if ( LoopOffset > pOwner->GetScale().x )
			{
				ImageOffset = pOwner->GetImage()->GetScale().x - pOwner->GetScale().x;
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
			if ( ImageOffset > pOwner->GetImage()->GetScale().x - pOwner->GetScale().x )
			{
				// ** 이미지 최하단 Offset으로 고정
				ImageOffset = pOwner->GetImage()->GetScale().x - pOwner->GetScale().x;

				// ** Loop 되어야 하는 상태라면
				if ( bLoop && !bDrawEachStartEnd )
				{
					LoopOffset = pOwner->GetScale().x;
					bDrawEachStartEnd = true;
				}
			}
		}
	}
}

void ScrollHorizontalBkg::Render(HDC _hdc)
{
	// ** 이미지 시작과 끝 연결 구간
	// ** Loop Scroll
	if ( bLoop && bDrawEachStartEnd )
	{
		TransparentBlt(_hdc,
			(int)(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
			(int)(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
			(int)(LoopOffset),
			(int)(pOwner->GetScale().y),
			pOwner->GetImage()->GetMemDC(),
			(int)(pOwner->GetImage()->GetScale().x - LoopOffset),
			(int)(pOwner->GetImage()->GetSegmentationScale().y * pOwner->GetImageOffsetOrder().y),
			(int)(LoopOffset),
			(int)(pOwner->GetImage()->GetSegmentationScale().y),
			RGB(255, 0, 255));

		TransparentBlt(_hdc,
			(int)((pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)) + LoopOffset),
			(int)(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
			(int)(pOwner->GetScale().x - LoopOffset),
			(int)(pOwner->GetScale().y),
			pOwner->GetImage()->GetMemDC(),
			0,
			(int)(pOwner->GetImage()->GetSegmentationScale().y * pOwner->GetImageOffsetOrder().y),
			(int)(pOwner->GetScale().x - LoopOffset),
			(int)(pOwner->GetImage()->GetSegmentationScale().y),
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
			(int)(ImageOffset),
			(int)(pOwner->GetImage()->GetSegmentationScale().y * pOwner->GetImageOffsetOrder().y),
			(int)(pOwner->GetScale().x),
			(int)(pOwner->GetImage()->GetSegmentationScale().y),
			RGB(255, 0, 255));
	}
}

void ScrollHorizontalBkg::Release()
{

}

void ScrollHorizontalBkg::StartLeft()
{
	ImageOffset = 0.0f;
}

void ScrollHorizontalBkg::StartRight()
{
	ImageOffset = pOwner->GetImage()->GetScale().x - pOwner->GetScale().x;
}

void ScrollHorizontalBkg::ScrollLeft()
{
	ScrollDirection = eScrollDirection::LEFT;
}

void ScrollHorizontalBkg::ScrollRight()
{
	ScrollDirection = eScrollDirection::RIGHT;
}