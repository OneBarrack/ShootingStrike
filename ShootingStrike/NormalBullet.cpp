#include "NormalBullet.h"
#include "Object.h"
#include "BitmapManager.h"

NormalBullet::NormalBullet()
{

}

NormalBullet::~NormalBullet()
{

}


void NormalBullet::Initialize()
{
	pBulletImage = BitmapManager::GetInstance()->GetImage(eImageKey::PROJECTILE);
	BulletImageScale = Vector3(230.0f, 230.0f);
	BulletRenderScale = Vector3(10.0f, 10.0f);

	Speed = 3.0f;

	DrawKey = "NormalBullet";
}

void NormalBullet::Update(Transform& _rTransInfo)
{
	_rTransInfo.Position.x += _rTransInfo.Direction.x * Speed;
	_rTransInfo.Position.y += _rTransInfo.Direction.y * Speed;

	//if (_rTransInfo.Position.x >= (WindowsWidth - 100))
		//return 1;
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
		(int)(pOwner->GetPosition().x - (BulletRenderScale.x * 0.5f)),
		(int)(pOwner->GetPosition().y - (BulletRenderScale.y * 0.5f)),
		(int)BulletRenderScale.x,
		(int)BulletRenderScale.y,
		pBulletImage->GetMemDC(),
		(int)BulletImageScale.x,
		0,
		(int)BulletImageScale.x,
		(int)BulletImageScale.y,
		RGB(255, 0, 255));
}
