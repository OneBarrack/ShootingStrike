#include "StageBackground.h"
#include "BitmapManager.h"

StageBackground::StageBackground()
{

}

StageBackground::~StageBackground()
{

}


void StageBackground::Initialize()
{
	TransInfo.Position = Vector3(0.0f, 0.0f);
	TransInfo.Direction = Vector3(0.0f, 0.0f);
	TransInfo.Scale = Vector3(0.0f, 0.0f);

	ObjectKey = eObjectKey::BULLET;
	Active = false;
}

int StageBackground::Update()
{

	return 0;
}

void StageBackground::Render(HDC _hdc)
{
	BitBlt(_hdc,
		0, 0,
		WindowsWidth,
		WindowsHeight,
		BitmapManager::GetInstance()->GetMemDC(eImageKey::BACKGROUND),
		0, 0,
		SRCCOPY);
}

void StageBackground::Release()
{

}
