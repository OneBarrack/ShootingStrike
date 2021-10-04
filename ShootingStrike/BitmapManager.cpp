#include "BitmapManager.h"

BitmapManager* BitmapManager::pInstance = nullptr;

void BitmapManager::Initialize()
{
	imageList[eImageKey::PLAYER]		= new Bitmap(eImageKey::PLAYER		 , L"../Resource/Player.bmp");
	imageList[eImageKey::BUFFER]		= new Bitmap(eImageKey::BUFFER		 , L"../Resource/Buffer.bmp");
	imageList[eImageKey::BACKGROUND]	= new Bitmap(eImageKey::BACKGROUND	 , L"../Resource/Background.bmp");
	imageList[eImageKey::LOGO]			= new Bitmap(eImageKey::LOGO		 , L"../Resource/Logo.bmp");
	imageList[eImageKey::LOGOBACK]		= new Bitmap(eImageKey::LOGOBACK	 , L"../Resource/LogoBack.bmp");
	imageList[eImageKey::STAGESIDEBACK] = new Bitmap(eImageKey::STAGESIDEBACK, L"../Resource/StageSideBack.bmp");
	imageList[eImageKey::STAGEBACK]		= new Bitmap(eImageKey::STAGEBACK	 , L"../Resource/StageBack.bmp");
	imageList[eImageKey::STAGECLOUD]	= new Bitmap(eImageKey::STAGECLOUD	 , L"../Resource/StageCloud.bmp");
	imageList[eImageKey::SCORE]			= new Bitmap(eImageKey::SCORE		 , L"../Resource/Score.bmp");
	imageList[eImageKey::NUMBER]		= new Bitmap(eImageKey::NUMBER		 , L"../Resource/Number.bmp");
	imageList[eImageKey::PLAYBUTTON]	= new Bitmap(eImageKey::PLAYBUTTON	 , L"../Resource/UI_Button_Play.bmp");
	imageList[eImageKey::BULLET]		= new Bitmap(eImageKey::BULLET		 , L"../Resource/Projectile.bmp");
	imageList[eImageKey::ANGEL]			= new Bitmap(eImageKey::ANGEL		 , L"../Resource/Angel.bmp");
	imageList[eImageKey::EXPLOSION]		= new Bitmap(eImageKey::EXPLOSION	 , L"../Resource/Effect_Explosion.bmp");
	imageList[eImageKey::HIT]			= new Bitmap(eImageKey::HIT			 , L"../Resource/Effect_Hit.bmp");
}

Bitmap* BitmapManager::GetImage(const eImageKey _key)
{ 
	auto FindImage = imageList.find(_key);
	if ( FindImage != imageList.end() )
		return FindImage->second;

	return nullptr;
}