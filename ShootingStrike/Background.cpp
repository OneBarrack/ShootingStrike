#include "Background.h"
#include "BitmapManager.h"

Background::Background()
{

}

Background::~Background()
{

}


void Background::Initialize()
{
	TransInfo.Position = Vector3(0.0f, 0.0f);
	TransInfo.Direction = Vector3(0.0f, 0.0f);
	TransInfo.Scale = Vector3(0.0f, 0.0f);

	Key = eObjectKey::BACKGROUND;
	Status = eObjectStatus::ACTIVATED;
	CollisionType = eCollisionType::NONE;
}

int Background::Update()
{

	return 0;
}

void Background::Render(HDC _hdc)
{
	BitBlt(_hdc,
		0, 0,
		WindowsWidth,
		WindowsHeight,
		BitmapManager::GetInstance()->GetMemDC(eImageKey::BACKGROUND),
		0, 0,
		SRCCOPY);
}

void Background::Release()
{

}

void Background::OnCollision(Object* _pObject)
{
}
