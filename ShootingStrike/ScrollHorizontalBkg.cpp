#include "ScrollHorizontalBkg.h"
#include "BitmapManager.h"

ScrollHorizontalBkg::ScrollHorizontalBkg()
	: ScrollDirection(eScrollDirection::LEFT)
	, ImageOffset(0.0f)
	, LoopOffset(0.0f)
	, bLoop(false)
	, bDrawEachStartEnd(false)
{
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
	ReceiveInfoFromOwner();

	// ** 윗방향 스크롤
	if ( ScrollDirection == eScrollDirection::LEFT )
	{
		// ** Loop를 위한 이미지 연결 작업중이라면
		if ( bDrawEachStartEnd )
		{
			LoopOffset += Speed;

			// ** 이미지 연결 구간이 끝났다면
			if ( LoopOffset > TransInfo.Scale.x )
			{
				ImageOffset = pImage->GetScale().x - TransInfo.Scale.x;
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
			if ( ImageOffset > pImage->GetScale().x - TransInfo.Scale.x )
			{
				// ** 이미지 최하단 Offset으로 고정
				ImageOffset = pImage->GetScale().x - TransInfo.Scale.x;

				// ** Loop 되어야 하는 상태라면
				if ( bLoop && !bDrawEachStartEnd )
				{
					LoopOffset = TransInfo.Scale.x;
					bDrawEachStartEnd = true;
				}
			}
		}
	}

	SendInfoToOwner();
}

void ScrollHorizontalBkg::Render(HDC _hdc)
{
	if ( !pImage ) 
		return;

	// ** 이미지 시작과 끝 연결 구간
	// ** Loop Scroll
	if ( bLoop && bDrawEachStartEnd )
	{
		TransparentBlt(_hdc,
			(int)(TransInfo.Position.x - (TransInfo.Scale.x * 0.5f)),
			(int)(TransInfo.Position.y - (TransInfo.Scale.y * 0.5f)),
			(int)(LoopOffset),
			(int)(TransInfo.Scale.y),
			pImage->GetMemDC(),
			(int)(pImage->GetScale().x - LoopOffset),
			(int)(pImage->GetSegmentationScale().y * pOwner->GetImageOffsetOrder().y),
			(int)(LoopOffset),
			(int)(pImage->GetSegmentationScale().y),
			RGB(255, 0, 255));

		TransparentBlt(_hdc,
			(int)((TransInfo.Position.x - (TransInfo.Scale.x * 0.5f)) + LoopOffset),
			(int)(TransInfo.Position.y - (TransInfo.Scale.y * 0.5f)),
			(int)(TransInfo.Scale.x - LoopOffset),
			(int)(TransInfo.Scale.y),
			pImage->GetMemDC(),
			0,
			(int)(pImage->GetSegmentationScale().y * pOwner->GetImageOffsetOrder().y),
			(int)(TransInfo.Scale.x - LoopOffset),
			(int)(pImage->GetSegmentationScale().y),
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
			(int)(ImageOffset),
			(int)(pImage->GetSegmentationScale().y * pOwner->GetImageOffsetOrder().y),
			(int)(TransInfo.Scale.x),
			(int)(pImage->GetSegmentationScale().y),
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