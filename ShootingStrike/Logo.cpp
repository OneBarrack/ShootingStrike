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
		
	Bridge* pBridge = nullptr;

	// ** Background
	pBridge = ObjectManager::GetInstance()->TakeBridge(eBridgeKey::BACKGROUND_SCROLL_HORIZONTAL);
	static_cast<ScrollHorizontalBkg*>(pBridge)->StartLeft();
	static_cast<ScrollHorizontalBkg*>(pBridge)->ScrollRight();
	static_cast<ScrollHorizontalBkg*>(pBridge)->SetLoop(true);

	pBackground = ObjectManager::GetInstance()->TakeObject(eObjectKey::BACKGROUND);
	pBackground->SetBridge(pBridge);
	pBackground->SetImage(eImageKey::LOGOBACK);
	pBackground->SetPosition(WindowsWidth * 0.5f, WindowsHeight * 0.5f);
	pBackground->SetScale(1915.0f, WindowsHeight);
	pBackground->SetSpeed(1.0f);	

	// ** Logo Title
	pBridge = ObjectManager::GetInstance()->TakeBridge(eBridgeKey::BACKGROUND_BASIC);
	pLogoTitle = ObjectManager::GetInstance()->TakeObject(eObjectKey::BACKGROUND);
	pLogoTitle->SetBridge(pBridge);
	pLogoTitle->SetImage(eImageKey::LOGO);
	pLogoTitle->SetPosition(WindowsWidth * 0.5f, WindowsHeight * 0.3f);
	pLogoTitle->SetScale(785.0f, 300.0f);

	// ** Play Button
	pPlayButton = ObjectManager::GetInstance()->TakeObject(eObjectKey::BUTTON);
	pPlayButton->SetImage(eImageKey::PLAYBUTTON);
	pPlayButton->SetPosition(WindowsWidth * 0.5f, WindowsHeight * 0.75f);
	pPlayButton->SetScale(150.0f, 70.0f);
	pPlayButton->SetCollider(pPlayButton->GetTransInfo());
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
	if ( pLogoTitle )  pLogoTitle->SetStatus(eObjectStatus::DESTROYED);
	if ( pPlayButton ) pPlayButton->SetStatus(eObjectStatus::DESTROYED);
}
