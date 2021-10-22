#include "Logo.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "BitmapManager.h"
#include "GameDataManager.h"
#include "GameDebugManager.h"
#include "InputManager.h"
#include "Player.h"
#include "RenderManager.h"

Logo::Logo()
	: hVideo(NULL)
	, tickTime(0)
	, videoPlayTime(0)
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

	Object* pPlayer = ObjectManager::GetInstance()->GetPlayer();
	if ( pPlayer )
	{
		pPlayer->Initialize();
	}
	else
	{
		pPlayer = ObjectManager::GetInstance()->NewObject(eObjectKey::PLAYER);
		ObjectManager::GetInstance()->SetPlayer(pPlayer);
	}	

	hVideo = MCIWndCreate(g_hWnd, NULL,
		MCIWNDF_NOPLAYBAR | WS_VISIBLE | WS_CHILD, L"../Resource/Video/Intro.wmv");

	MoveWindow(hVideo, 0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT, NULL);
	MCIWndPlay(hVideo);
	
	tickTime = GetTickCount64();
	videoPlayTime = 10000;

	/******* Logo Start *******/
	Start();
}

void Logo::Update()
{	
	ObjectManager::GetInstance()->Update();

	// ** video play time이 끝나거나 Enter, Space, Z, X를 누를 경우 다음 Scene으로 이동
	if ( tickTime + videoPlayTime < GetTickCount64() ||
		CHECK_KEYINPUT_STATE(eInputKey::KEY_ENTER, eKeyInputState::DOWN) ||
		CHECK_KEYINPUT_STATE(eInputKey::KEY_SPACE, eKeyInputState::DOWN) ||
		CHECK_KEYINPUT_STATE(eInputKey::KEY_Z, eKeyInputState::DOWN) ||
		CHECK_KEYINPUT_STATE(eInputKey::KEY_X, eKeyInputState::DOWN) )
	{
		SceneManager::GetInstance()->SetScene(eSCENEID::MENU);
	}

	// ** ESC 누를경우 프로그램 종료
	if ( CHECK_KEYINPUT_STATE(eInputKey::KEY_ESCAPE, eKeyInputState::DOWN) )
	{
		PostQuitMessage(NULL);
	}
}

void Logo::Render(HDC _hdc)
{
	ObjectManager::GetInstance()->Render(_hdc);

	RenderManager::FadeOut(_hdc);
}

void Logo::Release()
{
	MCIWndClose(hVideo);
}

void Logo::Start()
{
	// ...
}