#include "Bitmap.h"


Bitmap::Bitmap(eImageKey _ImageKey, const LPCWSTR _FileName)
	: hdc(NULL)
	, MemDC(NULL)
	, hBitmap(NULL)
	, OldBitmap(NULL)
	, ImageScale(Vector3())
	, SegmentationScale(Vector3())
{
	Initialize(_ImageKey, _FileName);
}

Bitmap::~Bitmap()
{
	Release();
}

void Bitmap::Initialize(eImageKey _ImageKey, const LPCWSTR _FileName)
{
	LoadBmp(_FileName);

	// ** Image Scale 정보 입력
	switch ( _ImageKey )
	{
		case eImageKey::BUFFER:
			ImageScale = Vector3(WindowsWidth, WindowsHeight);
			SegmentationScale = ImageScale;
			break;
		case eImageKey::BACKGROUND:
			ImageScale = Vector3(WindowsWidth, WindowsHeight);
			SegmentationScale = ImageScale;
			break;
		case eImageKey::LOGO:
			ImageScale = Vector3(923.0f, 350.0f);
			SegmentationScale = ImageScale;
			break;
		case eImageKey::LOGOBACK:
			ImageScale = Vector3(1915.0f, 720.0f);
			SegmentationScale = ImageScale;
			break;
		case eImageKey::STAGEBACK:
			ImageScale = Vector3(600.0f, 5527.0f);
			SegmentationScale = ImageScale;
			break;
		case eImageKey::STAGESIDEBACK:
			ImageScale = Vector3(608.0f, 800.0f);
			SegmentationScale = Vector3(ImageScale.x * 0.5f, ImageScale.y);
			break;
		case eImageKey::STAGECLOUD:
			//ImageScale = Vector3(1915.0f, 720.0f);
			//SegmentationScale = ImageScale;
			break;
		case eImageKey::PLAYBUTTON:
			ImageScale = Vector3(450.0f, 70.0f);
			SegmentationScale = Vector3(150.0f, 70.0f);
			break;
		case eImageKey::PLAYER:
			ImageScale = Vector3(131.0f, 141.0f);
			SegmentationScale = Vector3(42.0f, 47.0f);
			break;
		case eImageKey::PROJECTILE:
			ImageScale = Vector3(450.0f, 70.0f);
			SegmentationScale = Vector3(230.0f, 230.0f);
			break;
		case eImageKey::MOLE:
			ImageScale = Vector3(149.0f, 124.0f);
			SegmentationScale = ImageScale;
			break;
		case eImageKey::EFFECT:
			//ImageScale = Vector3(149.0f, 124.0f);
			//SegmentationScale = ImageScale;
			break;
		// ** eImageKey::KEYMAX
		default: 
			break;
	}
}

void Bitmap::LoadBmp(const LPCWSTR _FileName)
{
	hdc = GetDC(g_hWnd);
	MemDC = CreateCompatibleDC(hdc);

	/*
	LoadImageW(
	_In_opt_ HINSTANCE hInst,
	_In_ LPCWSTR name,
	_In_ UINT type,
	_In_ int cx,
	_In_ int cy,
	_In_ UINT fuLoad);
	*/

	hBitmap = (HBITMAP)LoadImage(NULL,
		_FileName, IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);



	OldBitmap = (HBITMAP)SelectObject(MemDC, hBitmap);

	ReleaseDC(g_hWnd, hdc);
}

void Bitmap::Release()
{
	SelectObject(MemDC, OldBitmap);
	DeleteObject(hBitmap);
	ReleaseDC(g_hWnd, MemDC);
}

