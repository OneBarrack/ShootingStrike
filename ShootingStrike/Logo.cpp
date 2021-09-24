#include "Logo.h"
#include "Player.h"
#include "Enemy.h"

#include "SceneManager.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"
#include "BitmapManager.h"
#include "Button.h"

Logo::Logo()
{

}

Logo::~Logo()
{
	Release();
}

void Logo::Initialize()
{
	BitmapManager::GetInstance()->Initialize();
	ObjectManager::GetInstance()->Initialize();

	ObjectManager::GetInstance()->SetPlayer(
		ObjectManager::GetInstance()->TakeObject(eObjectKey::PLAYER));
		
	pPlayButton = ObjectManager::GetInstance()->TakeObject(eObjectKey::BUTTON);	
	pPlayButton->SetPosition(WindowsWidth * 0.5f, WindowsHeight * 0.75f);
	pPlayButton->SetScale(150.0f, 70.0f);
	pPlayButton->SetColliderPosition(pPlayButton->GetPosition());
	pPlayButton->SetColliderScale(pPlayButton->GetScale());
	static_cast<Button*>(pPlayButton)->SetImage(BitmapManager::GetInstance()->GetImage(eImageKey::PLAYBUTTON));
}

void Logo::Update()
{
	pPlayButton->Update();

	if ( static_cast<Button*>(pPlayButton)->OnClick() )
	{	
		// ** MENU 구현 필요. 임시로 Stage로 바로 넘어감
		//SceneManager::GetInstance()->SetScene(eSCENEID::MENU);

		SceneManager::GetInstance()->SetScene(eSCENEID::STAGE);
	}
}

void Logo::Render(HDC _hdc)
{
	// ** 배경
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
			BitmapManager::GetInstance()->GetImage(eImageKey::LOGOBACK)->GetMemDC(),
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
			BitmapManager::GetInstance()->GetImage(eImageKey::LOGOBACK)->GetMemDC(),
			Offset1,
			0,
			SRCCOPY);

		BitBlt(_hdc,
			WindowsWidth - Offset2,
			0,
			Offset2,
			WindowsHeight,
			BitmapManager::GetInstance()->GetImage(eImageKey::LOGOBACK)->GetMemDC(),
			0,
			0,
			SRCCOPY);		
	}
	Offset1 += speed;
	Offset2 += speed;

	// ** 로고
	Vector3 LogoScale = Vector3(923.0f, 350.0f);
	TransparentBlt(_hdc,
		(int)(WindowsWidth * 0.5f - LogoScale.x * 0.5f),
		(int)(WindowsHeight * 0.3f - LogoScale.y * 0.5f),
		(int)LogoScale.x,
		(int)LogoScale.y,
		BitmapManager::GetInstance()->GetImage(eImageKey::LOGO)->GetMemDC(),
		0,
		0,
		(int)LogoScale.x,
		(int)LogoScale.y,
		RGB(255, 0, 255));

	// ** 버튼
	pPlayButton->Render(_hdc);

	/// gif돌리기
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
	if ( pPlayButton )
	{
		pPlayButton->Release();
		ObjectManager::GetInstance()->RecallObject(pPlayButton);
	}
}
