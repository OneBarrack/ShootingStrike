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
	Vector3 ImageScale = Vector3(230.0f, 230.0f);

	TransparentBlt(_hdc, // ** 최종 출력 위치
		(int)(RootObject->GetPosition().x - 5),
		(int)(RootObject->GetPosition().y - 5),
		10,
		10,
		BitmapManager::GetInstance()->GetMemDC(eImageKey::PROJECTILE),
		ImageScale.x,
		0,
		(int)(ImageScale.x),
		(int)(ImageScale.y),
		RGB(255, 0, 255));

	/*Ellipse(_hdc,
		int(RootObject->GetPosition().x - (RootObject->GetScale().x / 2)),
		int(RootObject->GetPosition().y - (RootObject->GetScale().y / 2)),
		int(RootObject->GetPosition().x + (RootObject->GetScale().x / 2)),
		int(RootObject->GetPosition().y + (RootObject->GetScale().y / 2)));*/
}

void NormalBullet::Release()
{

}
