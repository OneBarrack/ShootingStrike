#include "NormalBullet.h"
#include "Object.h"

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
	/*
	TransparentBlt(_hdc, // ** 최종 출력 위치
		int(TransInfo.Position.x - (TransInfo.Scale.x / 2)),
		int(TransInfo.Position.y + (TransInfo.Scale.x / 2) - Offset.y - 50),
		int(TransInfo.Scale.x),
		int(Offset.y),
		ImageList[Drawkey]->GetMemDC(),
		0, 0,
		int(TransInfo.Scale.x),
		int(Offset.y),
		RGB(255, 0, 255));
	*/

	Ellipse(_hdc,
		int(RootObject->GetPosition().x - (RootObject->GetScale().x / 2)),
		int(RootObject->GetPosition().y - (RootObject->GetScale().y / 2)),
		int(RootObject->GetPosition().x + (RootObject->GetScale().x / 2)),
		int(RootObject->GetPosition().y + (RootObject->GetScale().y / 2)));
}

void NormalBullet::Release()
{

}
