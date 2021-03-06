#include "ScrollHorizontalBkg.h"
#include "BitmapManager.h"

ScrollHorizontalBkg::ScrollHorizontalBkg()
	: scrollDirection(eScrollDirection::LEFT)
	, imageOffset(0.0f)
	, imageOffsetForRestart(0.0f)
	, maxLoopCount(0)
	, curLoopCount(0)
	, bDrawEachStartEnd(false)
	, curMoveDist(0)
{
}

ScrollHorizontalBkg::~ScrollHorizontalBkg()
{
}

void ScrollHorizontalBkg::Initialize()
{
	Super::Initialize();

	key = eBridgeKey::BACKGROUND_SCROLL_HORIZONTAL;
	scrollDirection = eScrollDirection::LEFT;
	imageOffset = 0.0f;
	maxLoopCount = 0;
	curLoopCount = 0;
	bDrawEachStartEnd = false;
	curMoveDist = 0;
}

void ScrollHorizontalBkg::Update()
{
	Super::Update();

	ReceiveInfoFromOwner();

	// ** 윗방향 스크롤
	if ( scrollDirection == eScrollDirection::LEFT )
	{
		// ** Loop를 위한 이미지 연결 작업중이라면
		if ( bDrawEachStartEnd )
		{
			imageOffsetForRestart += speed;

			// ** 이미지 연결 구간이 끝났다면
			if ( imageOffsetForRestart > transInfo.Scale.x )
			{
				imageOffset = pImage->GetScale().x - transInfo.Scale.x;
				bDrawEachStartEnd = false;
			}
		}
		else
		{
			imageOffset -= speed;

			// ** 이미지 끝에 도달했다면
			if ( imageOffset < 0.0f )
			{
				// ** 이미지 끝 Offset으로 고정
				imageOffset = 0.0f;

				// ** Loop 되어야 하는 상태라면
				if ( curLoopCount < maxLoopCount && !bDrawEachStartEnd )
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
			if ( imageOffset > pImage->GetScale().x - transInfo.Scale.x )
			{
				// ** 이미지 최하단 Offset으로 고정
				imageOffset = pImage->GetScale().x - transInfo.Scale.x;

				// ** Loop 되어야 하는 상태라면
				if ( curLoopCount < maxLoopCount && !bDrawEachStartEnd )
				{
					imageOffsetForRestart = transInfo.Scale.x;
					bDrawEachStartEnd = true;
				}
			}
		}
	}

	// ** Map 전체 진행도 계산
	if ( pImage )
	{
		float maxDist = pImage->GetScale().y + (pImage->GetScale().y * maxLoopCount) - WINDOWS_HEIGHT;

		if ( curMoveDist < maxDist )
			curMoveDist += speed;

		mapProgressRatio = curMoveDist / maxDist;
	}

	SendInfoToOwner();
}

void ScrollHorizontalBkg::Render(HDC _hdc)
{
	Super::Render(_hdc);

	if ( !pImage ) 
		return;

	static bool isLoopPrevScroll = false;

	// ** 이미지 시작과 끝 연결 구간
	// ** Loop Scroll
	if ( curLoopCount < maxLoopCount && bDrawEachStartEnd )
	{
		if ( isLoopPrevScroll == false )
		{
			isLoopPrevScroll = true;
		}

		TransparentBlt(_hdc,
			(int)(transInfo.Position.x - (transInfo.Scale.x * 0.5f)),
			(int)(transInfo.Position.y - (transInfo.Scale.y * 0.5f)),
			(int)(imageOffsetForRestart),
			(int)(transInfo.Scale.y),
			pImage->GetMemDC(),
			(int)(pImage->GetScale().x - imageOffsetForRestart),
			(int)(pImage->GetSegmentationScale().y * pOwner->GetImageOffsetOrder().y),
			(int)(imageOffsetForRestart),
			(int)(pImage->GetSegmentationScale().y),
			RGB(255, 0, 255));

		TransparentBlt(_hdc,
			(int)((transInfo.Position.x - (transInfo.Scale.x * 0.5f)) + imageOffsetForRestart),
			(int)(transInfo.Position.y - (transInfo.Scale.y * 0.5f)),
			(int)(transInfo.Scale.x - imageOffsetForRestart),
			(int)(transInfo.Scale.y),
			pImage->GetMemDC(),
			0,
			(int)(pImage->GetSegmentationScale().y * pOwner->GetImageOffsetOrder().y),
			(int)(transInfo.Scale.x - imageOffsetForRestart),
			(int)(pImage->GetSegmentationScale().y),
			RGB(255, 0, 255));
	}
	// ** 일반 Scroll
	else
	{
		if ( isLoopPrevScroll == true )
		{
			++curLoopCount;
			isLoopPrevScroll = false;
		}

		TransparentBlt(_hdc,
			(int)(transInfo.Position.x - (transInfo.Scale.x * 0.5f)),
			(int)(transInfo.Position.y - (transInfo.Scale.y * 0.5f)),
			(int)(transInfo.Scale.x),
			(int)(transInfo.Scale.y),
			pImage->GetMemDC(),
			(int)(imageOffset),
			(int)(pImage->GetSegmentationScale().y * pOwner->GetImageOffsetOrder().y),
			(int)(transInfo.Scale.x),
			(int)(pImage->GetSegmentationScale().y),
			RGB(255, 0, 255));
	}
}

void ScrollHorizontalBkg::Release()
{
	Super::Release();
}

void ScrollHorizontalBkg::StartLeft()
{
	imageOffset = 0.0f;
}

void ScrollHorizontalBkg::StartRight()
{
	imageOffset = pOwner->GetImage()->GetScale().x - pOwner->GetScale().x;
}

void ScrollHorizontalBkg::ScrollLeft()
{
	scrollDirection = eScrollDirection::LEFT;
}

void ScrollHorizontalBkg::ScrollRight()
{
	scrollDirection = eScrollDirection::RIGHT;
}