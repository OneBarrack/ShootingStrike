#include "Logo.h"
#include "SceneManager.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"
#include "BitmapManager.h"
#include "GameDataManager.h"
#include "GameDebugManager.h"
#include "InputManager.h"
#include "ScrollHorizontalBkg.h"
#include "ScrollVerticalBkg.h"
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
	// ** Initialize
	BitmapManager::GetInstance()->Initialize();
	ObjectManager::GetInstance()->Initialize();
	GameDataManager::GetInstance()->Initialize();
	GameDebugManager::GetInstance()->Initialize();

	ObjectManager::GetInstance()->SetPlayer(
		ObjectManager::GetInstance()->NewObject(eObjectKey::PLAYER));

	isStartingScene = true;

	Bridge* pBridge = nullptr;
	
	// ** Background
	//pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::BACKGROUND_SCROLL_HORIZONTAL);
	//pBackground = ObjectManager::GetInstance()->NewObject(eObjectKey::BACKGROUND);
	//pBackground->SetImage(eImageKey::LOGOBACK);
	//pBackground->SetPosition(WINDOWS_WIDTH * 0.5f, WINDOWS_HEIGHT * 0.5f);
	//pBackground->SetScale(1915.0f, WINDOWS_HEIGHT);
	//pBackground->SetSpeed(1.0f);	
	//pBackground->SetBridge(pBridge);
	//static_cast<ScrollHorizontalBkg*>(pBridge)->StartLeft();
	//static_cast<ScrollHorizontalBkg*>(pBridge)->ScrollRight();
	//static_cast<ScrollHorizontalBkg*>(pBridge)->SetLoop(true);

	pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::BACKGROUND_SCROLL_VERTICAL);
	pBackground = ObjectManager::GetInstance()->NewObject(eObjectKey::BACKGROUND);
	pBackground->SetImage(eImageKey::LOGOBACK);
	pBackground->SetPosition(WINDOWS_WIDTH * 0.5f, WINDOWS_HEIGHT * 0.5f);
	pBackground->SetScale(WINDOWS_WIDTH, WINDOWS_HEIGHT);
	pBackground->SetSpeed(0.5f);
	pBackground->SetBridge(pBridge);
	static_cast<ScrollVerticalBkg*>(pBridge)->StartBottom();
	static_cast<ScrollVerticalBkg*>(pBridge)->ScrollUp();
	static_cast<ScrollVerticalBkg*>(pBridge)->SetLoop(false);

	// ** Logo Title
	//pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::BACKGROUND_BASIC);
	//pLogoTitle = ObjectManager::GetInstance()->NewObject(eObjectKey::BACKGROUND);
	//pLogoTitle->SetImage(eImageKey::LOGO);
	//pLogoTitle->SetPosition(WINDOWS_WIDTH * 0.5f, WINDOWS_HEIGHT * 0.3f);
	//pLogoTitle->SetScale(785.0f, 300.0f);
	//pLogoTitle->SetBridge(pBridge);

	// ** Play Button
	pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::UI_BUTTON);
	pPlayButton = ObjectManager::GetInstance()->NewObject(eObjectKey::UI);
	pPlayButton->SetImage(eImageKey::PLAYBUTTON);
	pPlayButton->SetPosition(WINDOWS_WIDTH * 0.5f, WINDOWS_HEIGHT * 0.75f);
	pPlayButton->SetScale(150.0f, 70.0f);
	pPlayButton->SetCollider(pPlayButton->GetTransInfo());
	pPlayButton->SetBridge(pBridge);

	/******* Logo Start *******/
	Start();
}

void Logo::Update()
{	
	// ** Scene 스타트 및 끝나는 시점이 아닌경우
	if ( !isStartingScene && !isEndingScene )
	{
		// ** 메뉴로 이동할 임시 Play 버튼.
		if ( static_cast<ButtonUI*>(pPlayButton->GetBridgeObject())->OnClick() )
		{
			isEndingScene = true;
		}

		// ** 임시 종료 테스트(ESC).
		if ( CHECK_KEYINPUT_STATE(eInputKey::KEY_ESCAPE, eKeyInputState::DOWN) )
			PostQuitMessage(NULL);
	}

	ObjectManager::GetInstance()->Update();
}

void Logo::Render(HDC _hdc)
{
	ObjectManager::GetInstance()->Render(_hdc);

	if ( isStartingScene && RenderManager::FadeIn(_hdc) )
	{
		isStartingScene = false;
	}

	if ( isEndingScene && RenderManager::FadeOut(_hdc) )
	{
		isEndingScene = false;
		SceneManager::GetInstance()->SetScene(eSCENEID::MENU);
	}
}

void Logo::Release()
{
	if ( pBackground )
		ObjectManager::GetInstance()->RecallObject(pBackground);
	pBackground = nullptr;
	
	if ( pLogoTitle )
		ObjectManager::GetInstance()->RecallObject(pLogoTitle);
	pLogoTitle = nullptr;
	
	if ( pPlayButton )
		ObjectManager::GetInstance()->RecallObject(pPlayButton);
	pPlayButton = nullptr;
}

void Logo::Start()
{
	// ...
}