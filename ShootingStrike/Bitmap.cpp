#include "Bitmap.h"


Bitmap::Bitmap(eImageKey _imageKey, const LPCWSTR _fileName)
	: hdc(NULL)
	, memDC(NULL)
	, hBitmap(NULL)
	, oldBitmap(NULL)
	, imageScale(Vector3())
	, segmentationScale(Vector3())
{
	imageKey = _imageKey;
	LoadBmp(_fileName);
	Initialize();
}

Bitmap::~Bitmap()
{
	Release();
}

void Bitmap::Initialize()
{
	// ** Image Scale 정보 입력
	switch ( imageKey )
	{
		case eImageKey::BUFFER:
			imageScale = Vector3(WINDOWS_WIDTH, WINDOWS_HEIGHT);
			segmentationScale = imageScale;
			break;
		case eImageKey::FADEBACK_BLACK:
			imageScale = Vector3(WINDOWS_WIDTH, WINDOWS_HEIGHT);
			segmentationScale = imageScale;
			break;
		case eImageKey::FADEBACK_RED:
			imageScale = Vector3(WINDOWS_WIDTH, WINDOWS_HEIGHT);
			segmentationScale = imageScale;
			break;
		case eImageKey::LOGO:
			imageScale = Vector3(923.0f, 350.0f);
			segmentationScale = imageScale;
			break;
		case eImageKey::LOGOBACK:			
			imageScale = Vector3(1280.0f, 1809.0f);
			segmentationScale = imageScale;
			break;
		case eImageKey::MENUBACK:
			imageScale = Vector3(16740.0f, 304.0f);
			segmentationScale = Vector3(540.0f, 304.0f);
			break;
		case eImageKey::STAGEBACK:
			//imageScale = Vector3(600.0f, 5527.0f);
			imageScale = Vector3(640.0f, 960.0f);
			segmentationScale = imageScale;
			break;
		case eImageKey::STAGESIDEBACK:
			//imageScale = Vector3(608.0f, 800.0f);
			imageScale = Vector3(640.0f, 720.0f);
			segmentationScale = Vector3(imageScale.x * 0.5f, imageScale.y);
			break;
		case eImageKey::WARNING:
			imageScale = Vector3(382.0f, 100.0f);
			segmentationScale = imageScale;
			break;
		case eImageKey::TEXT:
			imageScale = Vector3(416.0f, 48.0f);
			segmentationScale = Vector3(16.0f, 16.0f);
			break;
		case eImageKey::SCORE:
			imageScale = Vector3(125.0f, 27.0f);
			segmentationScale = Vector3(25.0f, 0.0f);
			break;
		case eImageKey::NUMBER:
			imageScale = Vector3(140.0f, 14.0f);
			segmentationScale = Vector3(14.0f, 0.0f);
			break;
		case eImageKey::GAMEOVER:
			imageScale = Vector3(640.0f, 720.0f);
			segmentationScale = imageScale;
			break;
		case eImageKey::PROGRESSBAR:
			imageScale = Vector3(535.0f, 192.0f);
			segmentationScale = Vector3(535.0f, 96.0f);
			break;
		case eImageKey::PLAYBUTTON:
			imageScale = Vector3(450.0f, 70.0f);
			segmentationScale = Vector3(150.0f, 70.0f);
			break;
		case eImageKey::PLAY_QUIT_BUTTON:
		case eImageKey::YES_NO_BUTTON:
			imageScale = Vector3(210.0f, 100.0f);
			segmentationScale = Vector3(70.0f, 50.0f);
			break;
		case eImageKey::PLAYER:
			imageScale = Vector3(131.0f, 141.0f);
			segmentationScale = Vector3(42.0f, 47.0f);
			break;
		case eImageKey::BULLET:
			imageScale = Vector3(472.0f, 702.0f);
			segmentationScale = Vector3(236.0f, 234.0f);
			break;
		case eImageKey::ITEM:
			imageScale = Vector3(490.0f, 140.0f);
			segmentationScale = Vector3(70.0f, 70.0f);
			break;
		case eImageKey::ENEMY_NORMAL:
			imageScale = Vector3(512.0f, 512.0f);
			segmentationScale = imageScale;
			break;
		case eImageKey::ENEMY_ANGEL:
			imageScale = Vector3(1792.0f, 1920.0f);
			segmentationScale = Vector3(224.0f, 320.0f);
			break;
		case eImageKey::EXPLOSION:
			imageScale = Vector3(2997.0f, 333.0f);
			segmentationScale = Vector3(333.0f, 333.0f);
			break;
		case eImageKey::HIT:
			imageScale = Vector3(200.0f, 50.0f);
			segmentationScale = Vector3(50.0f, 50.0f);
			break;
		// ** eImageKey::KEYMAX
		default: 
			break;
	}
}

void Bitmap::LoadBmp(const LPCWSTR _FileName)
{
	hdc = GetDC(g_hWnd);
	memDC = CreateCompatibleDC(hdc);

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



	oldBitmap = (HBITMAP)SelectObject(memDC, hBitmap);

	ReleaseDC(g_hWnd, hdc);
}

void Bitmap::Release()
{
	SelectObject(memDC, oldBitmap);
	DeleteObject(hBitmap);
	ReleaseDC(g_hWnd, memDC);
}

