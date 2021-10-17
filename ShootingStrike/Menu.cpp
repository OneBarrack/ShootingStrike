#include "Menu.h"
#include "SceneManager.h"
#include "BitmapManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "ScrollHorizontalBkg.h"
#include "ScrollVerticalBkg.h"
#include "BasicBkg.h"
#include "ButtonUI.h"
#include "RenderManager.h"

Menu::Menu()
	: pBackground(nullptr)
{

}

Menu::~Menu()
{
	Release();
}

void Menu::Initialize()
{
	/******* Menu Start *******/
	bSceneStart = true;

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
}

void Menu::Update()
{
	// ** Play : Stage로 이동
	if ( static_cast<ButtonUI*>(pPlayButton->GetBridgeObject())->OnClick() )
	{
		static_cast<BasicBkg*>(pBackground->GetBridgeObject())->StopAnimation();
		bSceneEnd = true;
	}
	
	// ** Quit : 종료
	if ( static_cast<ButtonUI*>(pQuitButton->GetBridgeObject())->OnClick() )
	{
		PostQuitMessage(NULL);
	}
	
	ObjectManager::GetInstance()->Update();
}

void Menu::Render(HDC _hdc)
{
	ObjectManager::GetInstance()->Render(_hdc);

	if ( bSceneStart && RenderManager::FadeIn(_hdc) )
	{
		bSceneStart = false;
		static_cast<BasicBkg*>(pBackground->GetBridgeObject())->PlayAnimation();
	}

	if ( bSceneEnd && RenderManager::FadeOut(_hdc) )
	{
		bSceneEnd = false;
		SceneManager::GetInstance()->SetScene(eSCENEID::STAGE);
	}
}

void Menu::Release()
{
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
