#include "LogoBackground.h"
#include "BitmapManager.h"

LogoBackground::LogoBackground() 
	: pLogoBkgImage(nullptr)
	, LogoBkgScale(Vector3())
	, LoopOffset1(0)
	, LoopOffset2(0)
	, ScrollSpeed(0)
	, bAttachBkg(false)
{
}

LogoBackground::~LogoBackground()
{
	Release();
}

void LogoBackground::Initialize()
{
	//** Logo background
	pLogoBkgImage = BitmapManager::GetInstance()->GetImage(eImageKey::LOGOBACK);
	LogoBkgScale = Vector3(1915.0f, 720.0f);
	LoopOffset1  = 0;
	LoopOffset2  = 0;
	bAttachBkg   = false;
	ScrollSpeed  = 1;
}

void LogoBackground::Update()
{

}

void LogoBackground::Render(HDC _hdc)
{
	// ** Logo background
	if ( pLogoBkgImage )
		RenderLogoBkg(_hdc);
}

void LogoBackground::Release()
{

}

void LogoBackground::RenderLogoBkg(HDC _hdc)
{
	// ** 이어 붙이는 중이 아닐 때 배경이 끝에 도달했다면
	if ( !bAttachBkg && LogoBkgScale.x < WindowsWidth + LoopOffset1 )
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
			pLogoBkgImage->GetMemDC(),
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
			pLogoBkgImage->GetMemDC(),
			LoopOffset1,
			0,
			SRCCOPY);

		BitBlt(_hdc,
			WindowsWidth - LoopOffset2,
			0,
			LoopOffset2,
			WindowsHeight,
			pLogoBkgImage->GetMemDC(),
			0,
			0,
			SRCCOPY);
	}

	LoopOffset1 += ScrollSpeed;
	LoopOffset2 += ScrollSpeed;
}
