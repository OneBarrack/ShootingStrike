#include "BitmapManager.h"

BitmapManager* BitmapManager::Instance = nullptr;

void BitmapManager::Initialize()
{
	ImageList[eImageKey::BUFFER]		= (new Bitmap)->LoadBmp(L"../Resource/Buffer.bmp");
	ImageList[eImageKey::BACKGROUND]	= (new Bitmap)->LoadBmp(L"../Resource/Background.bmp");
	ImageList[eImageKey::LOGOBACK]		= (new Bitmap)->LoadBmp(L"../Resource/LogoBack.bmp");
	ImageList[eImageKey::STAGESIDEBACK]	= (new Bitmap)->LoadBmp(L"../Resource/StageSideBack.bmp");
	ImageList[eImageKey::STAGEBACK]		= (new Bitmap)->LoadBmp(L"../Resource/StageBack.bmp");	
	ImageList[eImageKey::STAGECLOUD]	= (new Bitmap)->LoadBmp(L"../Resource/StageCloud.bmp");
	ImageList[eImageKey::PROJECTILE]	= (new Bitmap)->LoadBmp(L"../Resource/Projectile.bmp");
	ImageList[eImageKey::HAMMER]		= (new Bitmap)->LoadBmp(L"../Resource/Hammer.bmp");
	ImageList[eImageKey::MOLE]			= (new Bitmap)->LoadBmp(L"../Resource/Mole.bmp");
	ImageList[eImageKey::HOLE]			= (new Bitmap)->LoadBmp(L"../Resource/Hole.bmp");
	ImageList[eImageKey::EFFECT]		= (new Bitmap)->LoadBmp(L"../Resource/Effect.bmp");
	ImageList[eImageKey::PLAYER]		= (new Bitmap)->LoadBmp(L"../Resource/Player.bmp");
}

HDC BitmapManager::GetMemDC(eImageKey _Key)
{
	return ImageList[_Key]->GetMemDC();
}
