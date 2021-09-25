#include "LogoTitle.h"
#include "BitmapManager.h"

LogoTitle::LogoTitle()
	: pLogoImage(nullptr)
	, LogoPosition(Vector3())
	, LogoScale(Vector3())
{
}

LogoTitle::~LogoTitle()
{
	Release();
}

void LogoTitle::Initialize()
{
	// ** Logo
	pLogoImage = BitmapManager::GetInstance()->GetImage(eImageKey::LOGO);
	LogoScale = Vector3(923.0f, 350.0f);
	LogoPosition = Vector3((WindowsWidth * 0.5f) - (LogoScale.x * 0.5f),
		(WindowsHeight * 0.3f) - (LogoScale.y * 0.5f));
}

void LogoTitle::Update()
{

}

void LogoTitle::Render(HDC _hdc)
{
	// ** Logo
	if ( pLogoImage )
		RenderLogo(_hdc);
}

void LogoTitle::Release()
{

}
void LogoTitle::RenderLogo(HDC _hdc)
{
	TransparentBlt(_hdc,
		(int)LogoPosition.x,
		(int)LogoPosition.y,
		(int)LogoScale.x,
		(int)LogoScale.y,
		pLogoImage->GetMemDC(),
		0,
		0,
		(int)LogoScale.x,
		(int)LogoScale.y,
		RGB(255, 0, 255));
}
