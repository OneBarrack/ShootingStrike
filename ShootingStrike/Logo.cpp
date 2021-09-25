#include "Logo.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"
#include "BitmapManager.h"
#include "ScrollHorizontalBkg.h"
#include "BasicBkg.h"
#include "Player.h"
#include "Enemy.h"
#include "Button.h"

Logo::Logo() 
	: pBackground(nullptr)
	, pLogoTitle(nullptr)
	, pPlayButton(nullptr)
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
		
	// ** Background
	Bridge* pBridge = new ScrollHorizontalBkg;
	static_cast<ScrollHorizontalBkg*>(pBridge)->SetLoopScroll(true);
	
	pBackground = ObjectManager::GetInstance()->TakeObject(eObjectKey::BACKGROUND, pBridge);
	pBackground->SetImage(BitmapManager::GetInstance()->GetImage(eImageKey::LOGOBACK));
	pBackground->SetSpeed(1.0f);
	
	Transform BackgroundTransInfo;
	BackgroundTransInfo.Position = Vector3(WindowsWidth * 0.5f, WindowsHeight * 0.5f);
	BackgroundTransInfo.Scale = Vector3(1915.0f, 720.0f);
	pBackground->SetTransInfo(BackgroundTransInfo);

	// ** Logo Title
	pBridge = new BasicBkg;
	pLogoTitle = ObjectManager::GetInstance()->TakeObject(eObjectKey::BACKGROUND, pBridge);
	pLogoTitle->SetImage(BitmapManager::GetInstance()->GetImage(eImageKey::LOGO));
	
	Transform LogoTransInfo;
	LogoTransInfo.Scale = Vector3(923.0f, 350.0f);
	LogoTransInfo.Position = Vector3((WindowsWidth * 0.5f) - (LogoTransInfo.Scale.x * 0.5f),
									 (WindowsHeight * 0.3f) - (LogoTransInfo.Scale.y * 0.5f));
	pLogoTitle->SetTransInfo(LogoTransInfo);

	// ** Play Button
	pPlayButton = ObjectManager::GetInstance()->TakeObject(eObjectKey::UI_BUTTON);
	static_cast<Button*>(pPlayButton)->SetImage(BitmapManager::GetInstance()->GetImage(eImageKey::PLAYBUTTON));	
	
	Transform PlayButtonTransInfo = Transform(WindowsWidth * 0.5f, WindowsHeight * 0.75f, 150.0f, 70.0f);
	pPlayButton->SetTransInfo(PlayButtonTransInfo);
	pPlayButton->SetCollider(PlayButtonTransInfo);
}

void Logo::Update()
{
	ObjectManager::GetInstance()->Update();

	if ( static_cast<Button*>(pPlayButton)->OnClick() )
	{	
		// ** MENU 구현 필요. 임시로 Stage로 바로 넘어감
		//SceneManager::GetInstance()->SetScene(eSCENEID::MENU);

		SceneManager::GetInstance()->SetScene(eSCENEID::STAGE);
	}
}

void Logo::Render(HDC _hdc)
{
	ObjectManager::GetInstance()->Render(_hdc);
}

void Logo::Release()
{
	if ( pBackground ) pBackground->SetStatus(eObjectStatus::DESTROYED);
	if ( pPlayButton ) pPlayButton->SetStatus(eObjectStatus::DESTROYED);
}
