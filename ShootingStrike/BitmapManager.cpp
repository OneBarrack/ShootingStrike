#include "BitmapManager.h"

BitmapManager* BitmapManager::Instance = nullptr;

void BitmapManager::Initialize()
{
	ImageList[eImageKey::BUFFER]		= new Bitmap(eImageKey::BUFFER		 , L"../Resource/Buffer.bmp");
	ImageList[eImageKey::BACKGROUND]	= new Bitmap(eImageKey::BACKGROUND	 , L"../Resource/Background.bmp");
	ImageList[eImageKey::LOGO]			= new Bitmap(eImageKey::LOGO		 , L"../Resource/Logo.bmp");
	ImageList[eImageKey::LOGOBACK]		= new Bitmap(eImageKey::LOGOBACK	 , L"../Resource/LogoBack.bmp");
	ImageList[eImageKey::STAGESIDEBACK] = new Bitmap(eImageKey::STAGESIDEBACK, L"../Resource/StageSideBack.bmp");
	ImageList[eImageKey::STAGEBACK]		= new Bitmap(eImageKey::STAGEBACK	 , L"../Resource/StageBack.bmp");
	ImageList[eImageKey::STAGECLOUD]	= new Bitmap(eImageKey::STAGECLOUD	 , L"../Resource/StageCloud.bmp");
	ImageList[eImageKey::PLAYBUTTON]	= new Bitmap(eImageKey::PLAYBUTTON	 , L"../Resource/UI_Button_Play.bmp");
	ImageList[eImageKey::PROJECTILE]	= new Bitmap(eImageKey::PROJECTILE	 , L"../Resource/Projectile.bmp");
	ImageList[eImageKey::MOLE]			= new Bitmap(eImageKey::MOLE		 , L"../Resource/Mole.bmp");
	ImageList[eImageKey::EFFECT]		= new Bitmap(eImageKey::EFFECT		 , L"../Resource/Effect.bmp");
	ImageList[eImageKey::PLAYER]		= new Bitmap(eImageKey::PLAYER		 , L"../Resource/Player.bmp");
}

Bitmap* BitmapManager::GetImage(const eImageKey _Key)
{ 
	auto FindImage = ImageList.find(_Key);
	if ( FindImage != ImageList.end() )
		return FindImage->second;

	return nullptr;
}