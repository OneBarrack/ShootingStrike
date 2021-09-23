#include "HammerEffect.h"
#include "ObjectManager.h"
#include "BitmapManager.h"

HammerEffect::HammerEffect()
{

}

HammerEffect::~HammerEffect()
{

}

void HammerEffect::Initialize()
{
	Frame = 0;

	Vector3 vPos = ObjectManager::GetInstance()->GetPlayer()->GetPosition();

	TransInfo.Position = Vector3(vPos.x, vPos.y);
	TransInfo.Scale = Vector3(366.0f, 312.0f);

	Collider.Position = Vector3(0.0f, 0.0f);
	Collider.Scale = Vector3(0.0f, 0.0f);

	Offset = Vector3(41.0f, -39.0f);

	Key = eObjectKey::HAMMEREFFECT;
	Status = eObjectStatus::DEACTIVATED;
	CollisionType = eCollisionType::RECT;
	bGenerateCollisionEvent = true;

	Time = GetTickCount64();
}

void HammerEffect::Update()
{
	if (Frame >= 8)
	{
		Status = eObjectStatus::DEACTIVATED;
		Frame = 0;
	}

	if (Time + 40 < GetTickCount64())
	{
		Time = GetTickCount64();
		Frame++;
	}
}

void HammerEffect::Render(HDC _hdc)
{
	TransparentBlt(_hdc, // ** 최종 출력 위치
		(int)TransInfo.Position.x - (int)(TransInfo.Scale.x * 0.5f) + (int)Offset.x,
		(int)TransInfo.Position.y - (int)(TransInfo.Scale.y * 0.5f) + (int)Offset.y,
		(int)TransInfo.Scale.x,
		(int)TransInfo.Scale.y,
		BitmapManager::GetInstance()->GetImage(eImageKey::EFFECT)->GetMemDC(),
		(int)TransInfo.Scale.x * Frame,
		(int)TransInfo.Scale.y * 0,
		(int)TransInfo.Scale.x,
		(int)TransInfo.Scale.y,
		RGB(255, 0, 255));
}

void HammerEffect::Release()
{

}

void HammerEffect::OnCollision(Object* _pObject)
{
}

