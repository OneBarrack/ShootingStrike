#include "StageBackground.h"
#include "BitmapManager.h"

StageBackground::StageBackground()
	: pStageBkgImage(nullptr)
	, StageBkgScale(Vector3())
	, StageBkgOffset(0.0f)
{
}

StageBackground::~StageBackground()
{
	Release();
}

void StageBackground::Initialize()
{
	// ** Stage background
	pStageBkgImage = BitmapManager::GetInstance()->GetImage(eImageKey::STAGEBACK);
	StageBkgScale = Vector3(600.f, 5527.0f);
	StageBkgOffset = 0.0f;

	// ** Owner Position, Scale 세팅
	Vector3 OwnerScale;
	OwnerScale.x = StageBkgScale.x < WindowsWidth ? StageBkgScale.x : WindowsWidth;
	OwnerScale.y = StageBkgScale.y < WindowsHeight ? StageBkgScale.y : WindowsHeight;

	pOwner->SetPosition(Vector3(WindowsWidth * 0.5f, WindowsHeight * 0.5f));
	pOwner->SetScale(OwnerScale);
}

void StageBackground::Update()
{
	// ** 화면의 끝과 Image의 끝이 만나는지 체크, 아직 만나지 않았다면 Offset 증가
	if ( StageBkgOffset < StageBkgScale.y - WindowsHeight )
	{
		StageBkgOffset += 0.5f;
	}

}

void StageBackground::Render(HDC _hdc)
{
	// ** Stage main background
	if ( pStageBkgImage )
		RenderStageBkg(_hdc);
}

void StageBackground::Release()
{

}

void StageBackground::RenderStageBkg(HDC _hdc)
{
	TransparentBlt(_hdc,
		(int)((WindowsWidth * 0.5f) - (StageBkgScale.x * 0.5f)),
		(int)0,
		(int)StageBkgScale.x,
		(int)WindowsHeight,
		BitmapManager::GetInstance()->GetImage(eImageKey::STAGEBACK)->GetMemDC(),
		(int)0,
		(int)(StageBkgScale.y - WindowsHeight - StageBkgOffset),
		(int)StageBkgScale.x,
		(int)WindowsHeight,
		RGB(255, 0, 255));
}
