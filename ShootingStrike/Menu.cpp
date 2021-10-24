#include "Menu.h"
#include "SceneManager.h"
#include "BitmapManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "SoundManager.h"
#include "ScrollHorizontalBkg.h"
#include "ScrollVerticalBkg.h"
#include "BasicBkg.h"
#include "ButtonUI.h"
#include "RenderManager.h"

Menu::Menu()
	: pBackground(nullptr)
	, pPlayButton(nullptr)
	, pQuitButton(nullptr)
{

}

Menu::~Menu()
{
	Release();
}

void Menu::Initialize()
{
	/******* Menu Start *******/
	isStartingScene = true;

	Bridge* pBridge = nullptr;

	// ** Background
	pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::BACKGROUND_BASIC);
	pBackground = ObjectManager::GetInstance()->NewObject(eObjectKey::BACKGROUND);
	pBackground->SetImage(eImageKey::MENUBACK);
	pBackground->SetPosition(WINDOWS_WIDTH * 0.5f, WINDOWS_HEIGHT * 0.5f);
	pBackground->SetScale(WINDOWS_WIDTH, WINDOWS_HEIGHT);
	pBackground->SetBridge(pBridge);	
	static_cast<BasicBkg*>(pBridge)->SetAnimationDelay(75);

	// ** Play Button
	pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::UI_BUTTON);
	pPlayButton = ObjectManager::GetInstance()->NewObject(eObjectKey::UI);
	pPlayButton->SetImage(eImageKey::PLAY_QUIT_BUTTON);
	pPlayButton->SetPosition(WINDOWS_WIDTH * 0.7f, WINDOWS_HEIGHT * 0.7f);
	pPlayButton->SetScale(140.0f, 50.0f);
	pPlayButton->SetCollider(pPlayButton->GetTransInfo());
	pPlayButton->SetBridge(pBridge);

	// ** Quit Button
	pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::UI_BUTTON);
	pQuitButton = ObjectManager::GetInstance()->NewObject(eObjectKey::UI);
	pQuitButton->SetImage(eImageKey::PLAY_QUIT_BUTTON);
	pQuitButton->SetPosition(WINDOWS_WIDTH * 0.7f, WINDOWS_HEIGHT * 0.8f);
	pQuitButton->SetScale(140.0f, 50.0f);
	pQuitButton->SetCollider(pQuitButton->GetTransInfo());
	pQuitButton->SetBridge(pBridge);
	static_cast<ButtonUI*>(pBridge)->SetButtonTypeIndex(1);	

	// ** Play BGM Sound
	SoundManager::GetInstance()->Play(eSoundKey::BGM_MENU);
}

void Menu::Update()
{
	// ** Scene 스타트 및 끝나는 시점이 아닌경우
	if ( !isStartingScene && !isEndingScene )
	{
		// ** Play : Stage로 이동
		if ( static_cast<ButtonUI*>(pPlayButton->GetBridgeObject())->OnClick() )
		{
			static_cast<BasicBkg*>(pBackground->GetBridgeObject())->StopAnimation();
			isEndingScene = true;
		}

		// ** Quit : 종료
		if ( static_cast<ButtonUI*>(pQuitButton->GetBridgeObject())->OnClick() )
		{
			PostQuitMessage(NULL);
		}
	}

	ObjectManager::GetInstance()->Update();
}

void Menu::Render(HDC _hdc)
{
	ObjectManager::GetInstance()->Render(_hdc);

	if ( isStartingScene && RenderManager::FadeIn(_hdc) )
	{
		isStartingScene = false;
		static_cast<BasicBkg*>(pBackground->GetBridgeObject())->PlayAnimation();
	}

	if ( isEndingScene && RenderManager::FadeOut(_hdc) )
	{
		isEndingScene = false;
		SceneManager::GetInstance()->SetScene(eSCENEID::STAGE);
	}
}

void Menu::Release()
{
	SoundManager::GetInstance()->Stop(eSoundKey::ALL);

	if ( pBackground )
		ObjectManager::GetInstance()->RecallObject(pBackground);
	pBackground = nullptr;
	if ( pPlayButton )
		ObjectManager::GetInstance()->RecallObject(pPlayButton);
	pPlayButton = nullptr;
	if ( pQuitButton )
		ObjectManager::GetInstance()->RecallObject(pQuitButton);
	pQuitButton = nullptr;	
}
