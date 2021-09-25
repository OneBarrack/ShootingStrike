#include "NormalBullet.h"
#include "Object.h"
#include "BitmapManager.h"

NormalBullet::NormalBullet() 
	: pBulletImage(nullptr)
	, BulletImageScale(Vector3())
{

}

NormalBullet::~NormalBullet()
{
	Release();
}


void NormalBullet::Initialize()
{
	pBulletImage = BitmapManager::GetInstance()->GetImage(eImageKey::PROJECTILE);
	BulletImageScale = Vector3(230.0f, 230.0f);
	
	DrawKey = "NormalBullet";
}

void NormalBullet::Update()
{
	TransInfo = pOwner->GetTransInfo();
	Speed = pOwner->GetSpeed();

	TransInfo.Position.x += TransInfo.Direction.x * Speed;
	TransInfo.Position.y += TransInfo.Direction.y * Speed;

	pOwner->SetTransInfo(TransInfo);
	pOwner->SetSpeed(Speed);
}


void NormalBullet::Render(HDC _hdc)
{
	if ( pBulletImage )
		RenderBullet(_hdc);
}

void NormalBullet::Release()
{

}

void NormalBullet::RenderBullet(HDC _hdc)
{
	TransparentBlt(_hdc, // ** 최종 출력 위치
		(int)(pOwner->GetPosition().x - (TransInfo.Scale.x * 0.5f)),
		(int)(pOwner->GetPosition().y - (TransInfo.Scale.y * 0.5f)),
		(int)TransInfo.Scale.x,
		(int)TransInfo.Scale.y,
		pBulletImage->GetMemDC(),
		(int)BulletImageScale.x,
		0,
		(int)BulletImageScale.x,
		(int)BulletImageScale.y,
		RGB(255, 0, 255));
}
