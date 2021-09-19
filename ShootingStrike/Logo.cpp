#include "Logo.h"
#include "Player.h"
#include "Enemy.h"

#include "SceneManager.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"
#include "BitmapManager.h"

Logo::Logo()
{

}

Logo::~Logo()
{

}

void Logo::Initialize()
{
	ObjectManager::GetInstance()->Initialize();

	ObjectManager::GetInstance()->SetPlayer(
		ObjectManager::GetInstance()->TakeObject(eObjectKey::PLAYER));

	BitmapManager::GetInstance()->Initialize();
}

void Logo::Update()
{
	if (GetAsyncKeyState('A'))
		SceneManager::GetInstance()->SetScene(eSCENEID::MENU);
}

void Logo::Render(HDC _hdc)
{
	Vector3 ImageScale = Vector3(1915.0f, 720.0f);
	int speed = 1;

	static int Offset1 = 0;
	static int Offset2 = 0;
	static bool bCross = false;

	if ( !bCross && ImageScale.x < WindowsWidth + Offset1 )
	{
		Offset2 = 0;
		bCross = true;
	}
	if ( bCross && WindowsWidth < Offset2 )
	{
		Offset1 = 0;
		bCross = false;
	}

	if ( !bCross )
	{
		BitBlt(_hdc,
			0,
			0,
			WindowsWidth,
			WindowsHeight,
			BitmapManager::GetInstance()->GetMemDC(eImageKey::LOGOBACK),
			Offset1,
			0,
			SRCCOPY);
	}
	else
	{
		BitBlt(_hdc,
			0,
			0,
			WindowsWidth - Offset2,
			WindowsHeight,
			BitmapManager::GetInstance()->GetMemDC(eImageKey::LOGOBACK),
			Offset1,
			0,
			SRCCOPY);

		BitBlt(_hdc,
			WindowsWidth - Offset2,
			0,
			Offset2,
			WindowsHeight,
			BitmapManager::GetInstance()->GetMemDC(eImageKey::LOGOBACK),
			0,
			0,
			SRCCOPY);		
	}
	Offset1 += speed;
	Offset2 += speed;
	/// gifµ¹¸®±â
	//412 232
	//static int Frame = 0;
	//static int Offset = 0;
	//Vector3 ImageScale = Vector3(412.0f, 232.0f);

	//StretchBlt(_hdc,
	//	0,
	//	0,
	//	504,
	//	304,
	//	BitmapManager::GetInstance()->GetMemDC(eImageKey::LOGOBACK),
	//	(int)(ImageScale.x * (Offset % 5)),
	//	(int)(ImageScale.y * (Offset / 5)),
	//	(int)ImageScale.x,
	//	(int)ImageScale.y,
	//	SRCCOPY);

	//if ( Frame % 3 == 0 )
	//{
	//	if ( Offset < 30 )
	//	{
	//		++Offset;
	//	}
	//	else
	//	{
	//		Offset = 0;
	//	}
	//}

	//++Frame;
}

void Logo::Release()
{

}
