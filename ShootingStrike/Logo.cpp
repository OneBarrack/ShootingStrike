#include "Logo.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"
#include "BitmapManager.h"
#include "LogoBackground.h"
#include "LogoTitle.h"
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
	Bridge* pBridge = new LogoBackground;
	pBackground = ObjectManager::GetInstance()->TakeObject(eObjectKey::BACKGROUND, pBridge);

	// ** Logo
	pBridge = new LogoTitle;
	pLogoTitle = ObjectManager::GetInstance()->TakeObject(eObjectKey::BACKGROUND, pBridge);

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
