#include "BitmapManager.h"

BitmapManager* BitmapManager::Instance = nullptr;

void BitmapManager::Initialize()
{
	ImageList[eImageKey::BUFFER]	  = (new Bitmap)->LoadBmp(L"../Resource/Buffer.bmp");
	ImageList[eImageKey::BACKGROUND]  = (new Bitmap)->LoadBmp(L"../Resource/Background.bmp");
	ImageList[eImageKey::HAMMER]	  = (new Bitmap)->LoadBmp(L"../Resource/Hammer.bmp");
	ImageList[eImageKey::MOLE]		  = (new Bitmap)->LoadBmp(L"../Resource/Mole.bmp");
	ImageList[eImageKey::HOLE]		  = (new Bitmap)->LoadBmp(L"../Resource/Hole.bmp");
	ImageList[eImageKey::EFFECT]	  = (new Bitmap)->LoadBmp(L"../Resource/Effect.bmp");
}

HDC BitmapManager::GetMemDC(eImageKey _Key)
{
	return ImageList[_Key]->GetMemDC();
}
