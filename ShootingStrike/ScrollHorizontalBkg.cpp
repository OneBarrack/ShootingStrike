#include "ScrollHorizontalBkg.h"
#include "BitmapManager.h"

ScrollHorizontalBkg::ScrollHorizontalBkg()
	: bLoopScroll(false)
	, LoopOffset1(0)
	, LoopOffset2(0)
	, bAttachBkg(false)
{
}

ScrollHorizontalBkg::~ScrollHorizontalBkg()
{
	Release();
}

void ScrollHorizontalBkg::Initialize()
{
	bLoopScroll = false;
	LoopOffset1 = 0;
	LoopOffset2 = 0;
	bAttachBkg = false;
}

void ScrollHorizontalBkg::Update()
{
}

void ScrollHorizontalBkg::Render(HDC _hdc)
{
	Bitmap* pImage = pOwner->GetImage();
	if ( !pImage )
		return;

	// ** 이어 붙이는 중이 아닐 때 배경이 끝에 도달했다면
	if ( !bAttachBkg && pOwner->GetScale().x < WindowsWidth + LoopOffset1 )
	{
		// ** 이어 붙이도록 Offset2과 bAttachBkg 세팅
		LoopOffset2 = 0;
		bAttachBkg = true;
	}

	// ** 이어 붙이는 중일 때 이어붙인 배경이 화면을 가득 채운다면
	if ( bAttachBkg && WindowsWidth < LoopOffset2 )
	{
		// ** 그리기 한 번에 화면을 다 채울 수 있도록 Offset1과 bAttachBkg 세팅
		LoopOffset1 = 0;
		bAttachBkg = false;
	}


	// ** 한 번에 그림
	if ( !bAttachBkg )
	{
		BitBlt(_hdc,
			0,
			0,
			WindowsWidth,
			WindowsHeight,
			pImage->GetMemDC(),
			LoopOffset1,
			0,
			SRCCOPY);
	}
	// ** 앞 부분, 뒷 부분 그리기로 나누어 이어붙임
	else
	{
		BitBlt(_hdc,
			0,
			0,
			WindowsWidth - LoopOffset2,
			WindowsHeight,
			pImage->GetMemDC(),
			LoopOffset1,
			0,
			SRCCOPY);

		BitBlt(_hdc,
			WindowsWidth - LoopOffset2,
			0,
			LoopOffset2,
			WindowsHeight,
			pImage->GetMemDC(),
			0,
			0,
			SRCCOPY);
	}

	LoopOffset1 += static_cast<int>(pOwner->GetSpeed());
	LoopOffset2 += static_cast<int>(pOwner->GetSpeed());
}

void ScrollHorizontalBkg::Release()
{

}
