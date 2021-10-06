#include "Logo.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"
#include "BitmapManager.h"
#include "GameDataManager.h"
#include "GameDebugManager.h"
#include "InputManager.h"
#include "ScrollHorizontalBkg.h"
#include "BasicBkg.h"
#include "Player.h"
#include "Enemy.h"
#include "ButtonUI.h"
#include "TextUI.h"

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
	GameDataManager::GetInstance()->Initialize();
	GameDebugManager::GetInstance()->Initialize();

	ObjectManager::GetInstance()->SetPlayer(
		ObjectManager::GetInstance()->NewObject(eObjectKey::PLAYER));
		
	Bridge* pBridge = nullptr;
	
	// ** Background
	pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::BACKGROUND_SCROLL_HORIZONTAL);
	pBackground = ObjectManager::GetInstance()->NewObject(eObjectKey::BACKGROUND);
	pBackground->SetImage(eImageKey::LOGOBACK);
	pBackground->SetPosition(WINDOWS_WIDTH * 0.5f, WINDOWS_HEIGHT * 0.5f);
	pBackground->SetScale(1915.0f, WINDOWS_HEIGHT);
	pBackground->SetSpeed(1.0f);	
	pBackground->SetBridge(pBridge);
	static_cast<ScrollHorizontalBkg*>(pBridge)->StartLeft();
	static_cast<ScrollHorizontalBkg*>(pBridge)->ScrollRight();
	static_cast<ScrollHorizontalBkg*>(pBridge)->SetLoop(true);

	// ** Logo Title
	pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::BACKGROUND_BASIC);
	pLogoTitle = ObjectManager::GetInstance()->NewObject(eObjectKey::BACKGROUND);
	pLogoTitle->SetImage(eImageKey::LOGO);
	pLogoTitle->SetPosition(WINDOWS_WIDTH * 0.5f, WINDOWS_HEIGHT * 0.3f);
	pLogoTitle->SetScale(785.0f, 300.0f);
	pLogoTitle->SetBridge(pBridge);

	// ** Play Button
	pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::UI_BUTTON);
	pPlayButton = ObjectManager::GetInstance()->NewObject(eObjectKey::UI);
	pPlayButton->SetImage(eImageKey::PLAYBUTTON);
	pPlayButton->SetPosition(WINDOWS_WIDTH * 0.5f, WINDOWS_HEIGHT * 0.75f);
	pPlayButton->SetScale(150.0f, 70.0f);
	pPlayButton->SetCollider(pPlayButton->GetTransInfo());
	pPlayButton->SetBridge(pBridge);		
}

void Logo::Update()
{
	ObjectManager::GetInstance()->Update();
	
	if ( static_cast<ButtonUI*>(pPlayButton->GetBridgeObject())->OnClick() )
	{	
		// ** MENU 구현 필요. 임시로 Stage로 바로 넘어감
		//SceneManager::GetInstance()->SetScene(eSCENEID::MENU);

		SceneManager::GetInstance()->SetScene(eSCENEID::STAGE);
	}

	// ** 임시 종료 테스트(ESC). 버튼 등 추가구현 필요
	if ( CHECK_KEYINPUT_STATE(eInputKey::KEY_ESCAPE, eKeyInputState::DOWN) )
		PostQuitMessage(NULL);
}

void Logo::Render(HDC _hdc)
{
	ObjectManager::GetInstance()->Render(_hdc);
}

void Logo::Release()
{
	if ( pBackground ) ObjectManager::GetInstance()->RecallObject(pBackground);
	if ( pLogoTitle )  ObjectManager::GetInstance()->RecallObject(pLogoTitle);
	if ( pPlayButton ) ObjectManager::GetInstance()->RecallObject(pPlayButton);
}
