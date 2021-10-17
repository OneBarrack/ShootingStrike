#include "BitmapManager.h"

BitmapManager* BitmapManager::pInstance = nullptr;

void BitmapManager::Initialize()
{
	imageList[eImageKey::PLAYER]			= new Bitmap(eImageKey::PLAYER			, L"../Resource/Player.bmp");
	imageList[eImageKey::BUFFER]			= new Bitmap(eImageKey::BUFFER			, L"../Resource/Buffer.bmp");
	imageList[eImageKey::FADEBACK]			= new Bitmap(eImageKey::FADEBACK		, L"../Resource/FadeBack.bmp");
	imageList[eImageKey::LOGO]				= new Bitmap(eImageKey::LOGO			, L"../Resource/Logo.bmp");
	imageList[eImageKey::LOGOBACK]			= new Bitmap(eImageKey::LOGOBACK		, L"../Resource/LogoBack.bmp");
	imageList[eImageKey::MENUBACK]			= new Bitmap(eImageKey::MENUBACK		, L"../Resource/MenuBack.bmp");
	imageList[eImageKey::STAGESIDEBACK]		= new Bitmap(eImageKey::STAGESIDEBACK	, L"../Resource/StageSideBack.bmp");
	imageList[eImageKey::STAGEBACK]			= new Bitmap(eImageKey::STAGEBACK		, L"../Resource/StageBack.bmp");
	imageList[eImageKey::STAGECLOUD]		= new Bitmap(eImageKey::STAGECLOUD		, L"../Resource/StageCloud.bmp");
	imageList[eImageKey::TEXT]				= new Bitmap(eImageKey::TEXT			, L"../Resource/Text.bmp");
	imageList[eImageKey::SCORE]				= new Bitmap(eImageKey::SCORE			, L"../Resource/Score.bmp");
	imageList[eImageKey::NUMBER]			= new Bitmap(eImageKey::NUMBER			, L"../Resource/Number.bmp");
	imageList[eImageKey::PROGRESSBAR]		= new Bitmap(eImageKey::PROGRESSBAR		, L"../Resource/UI_ProgressBar.bmp");
	imageList[eImageKey::PLAYBUTTON]		= new Bitmap(eImageKey::PLAYBUTTON		, L"../Resource/UI_Button_Play.bmp");
	imageList[eImageKey::PLAY_QUIT_BUTTON]  = new Bitmap(eImageKey::PLAY_QUIT_BUTTON, L"../Resource/UI_Button_Play_Quit.bmp");
	imageList[eImageKey::BULLET]			= new Bitmap(eImageKey::BULLET			, L"../Resource/Projectile.bmp");
	imageList[eImageKey::ANGEL]				= new Bitmap(eImageKey::ANGEL			, L"../Resource/Angel.bmp");
	imageList[eImageKey::EXPLOSION]			= new Bitmap(eImageKey::EXPLOSION		, L"../Resource/Effect_Explosion.bmp");
	imageList[eImageKey::HIT]				= new Bitmap(eImageKey::HIT				, L"../Resource/Effect_Hit.bmp");
}

Bitmap* BitmapManager::GetImage(const eImageKey _key)
{ 
	auto FindImage = imageList.find(_key);
	if ( FindImage != imageList.end() )
		return FindImage->second;

	return nullptr;
}