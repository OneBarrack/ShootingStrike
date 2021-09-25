#include "StageSideBackground.h"
#include "BitmapManager.h"

StageSideBackground::StageSideBackground()
	: pStageSideBkgImage(nullptr)
	, SideBkgScale(Vector3())
	, SideBkgOffset(0.0f)
{
}

StageSideBackground::~StageSideBackground()
{
	Release();
}

void StageSideBackground::Initialize()
{
	// ** Stage side background
	pStageSideBkgImage = BitmapManager::GetInstance()->GetImage(eImageKey::STAGESIDEBACK);
	SideBkgScale = Vector3(608.0f, 800.0f);
	SideBkgOffset = 340.0f;
}

void StageSideBackground::Update()
{

}

void StageSideBackground::Render(HDC _hdc)
{
	// ** Stage side background
	if ( pStageSideBkgImage )
		RenderStageSideBkg(_hdc);
}

void StageSideBackground::Release()
{

}

void StageSideBackground::RenderStageSideBkg(HDC _hdc)
{
	TransparentBlt(_hdc,
		(int)0,
		(int)0,
		(int)SideBkgOffset,
		(int)WindowsHeight,
		BitmapManager::GetInstance()->GetImage(eImageKey::STAGESIDEBACK)->GetMemDC(),
		(int)0,
		(int)0,
		(int)(SideBkgScale.x * 0.5f),
		(int)WindowsHeight,
		RGB(255, 0, 255));

	TransparentBlt(_hdc,
		(int)(WindowsWidth - SideBkgOffset),
		(int)0,
		(int)SideBkgOffset,
		(int)WindowsHeight,
		BitmapManager::GetInstance()->GetImage(eImageKey::STAGESIDEBACK)->GetMemDC(),
		(int)(SideBkgScale.x * 0.5f),
		(int)0,
		(int)(SideBkgScale.x * 0.5f),
		(int)WindowsHeight,
		RGB(255, 0, 255));
}
