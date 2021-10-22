#include "GameClearUI.h"
#include "BitmapManager.h"
#include "ObjectManager.h"
#include "GameDataManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Bridge.h"
#include "TextUI.h"

GameClearUI::GameClearUI()
	: pGameClearImage(nullptr)
	, pFadeBackImage(nullptr)
	, pPlayTimeNameTextUI(nullptr)
	, pPlayTimeTextUI(nullptr)
	, pScoreNameTextUI(nullptr)
	, pScoreUI(nullptr)
	, pPressEnterTextUI(nullptr)
	, bInitializedObjects(false)
	, alpha(0)
	, fadeSpeed(0)
{

}

GameClearUI::~GameClearUI()
{
}


void GameClearUI::Initialize()
{
	Super::Initialize();

	key = eBridgeKey::UI_GAMECLEAR;

	pGameClearImage = BitmapManager::GetInstance()->GetImage(eImageKey::GAMECLEAR);
	pFadeBackImage = BitmapManager::GetInstance()->GetImage(eImageKey::FADEBACK_WHITE);
		
	bInitializedObjects = false;
	alpha = 0;
	fadeSpeed = 1;

	InitTextObjects();
}

void GameClearUI::Update()
{
	Super::Update();

	if ( bInitializedObjects )
	{
		// ** Enter 입력 시 LOGO로 이동
		if ( CHECK_KEYINPUT_STATE(eInputKey::KEY_ENTER, eKeyInputState::DOWN) )
		{
			SceneManager::GetInstance()->SetScene(eSCENEID::LOGO);
		}
	}
	else
	{
		InitTextObjects();
	}
}

void GameClearUI::Render(HDC _hdc)
{
	Super::Render(_hdc);

	if ( !pGameClearImage )
		return;

	// ** alpha가 100보다 작은 경우에 alpha 증가
	if ( alpha < 100 )
		alpha += fadeSpeed;

	BLENDFUNCTION bf;
	bf.AlphaFormat = 0;			// ** 일반 비트맵 0, 32비트 비트맵 AC_SRC_ALPHA
	bf.BlendFlags = 0;			// ** 사용되지 않는 옵션. 무조건 0
	bf.BlendOp = AC_SRC_OVER;  // ** AC_SRC_OVER
	bf.SourceConstantAlpha = alpha;		// ** 투명도(투명 0 - 불투명 255)

	// ** Fade Background 이미지를 바탕으로 Fade 효과 부여
	AlphaBlend(_hdc, 0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT,
		pFadeBackImage->GetMemDC(),
		0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT, bf);

	TransparentBlt(_hdc, // ** 최종 출력 위치
		int(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
		int(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
		int(pOwner->GetScale().x),
		int(pOwner->GetScale().y),
		pGameClearImage->GetMemDC(),
		int(0),
		int(0),
		int(pGameClearImage->GetSegmentationScale().x),
		int(pGameClearImage->GetSegmentationScale().y),
		RGB(255, 0, 255));
}

void GameClearUI::Release()
{
	Super::Release();

	pGameClearImage = nullptr;
	pFadeBackImage = nullptr;

	if ( pPlayTimeNameTextUI )
		ObjectManager::GetInstance()->RecallObject(pPlayTimeNameTextUI);
	pPlayTimeNameTextUI = nullptr;

	if ( pPlayTimeTextUI )
		ObjectManager::GetInstance()->RecallObject(pPlayTimeTextUI);
	pPlayTimeTextUI = nullptr;

	if ( pScoreNameTextUI )
		ObjectManager::GetInstance()->RecallObject(pScoreNameTextUI);
	pScoreNameTextUI = nullptr;

	if ( pScoreUI )
		ObjectManager::GetInstance()->RecallObject(pScoreUI);
	pScoreUI = nullptr;

	if ( pPressEnterTextUI )
		ObjectManager::GetInstance()->RecallObject(pPressEnterTextUI);
	pPressEnterTextUI = nullptr;
}

void GameClearUI::InitTextObjects()
{
	if ( pOwner )
	{		
		Bridge* pBridge;

		// ** Play Time Name Text UI
		pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::UI_TEXT);
		pPlayTimeNameTextUI = ObjectManager::GetInstance()->NewObject(eObjectKey::UI);
		pPlayTimeNameTextUI->SetPosition(
			pOwner->GetPosition().x - (pOwner->GetScale().x * 0.35f),
			pOwner->GetPosition().y + (pOwner->GetScale().y * 0.24f));
		pPlayTimeNameTextUI->SetScale(100.0f, 50.0f);
		pPlayTimeNameTextUI->SetBridge(pBridge);
		static_cast<TextUI*>(pBridge)->SetText("PLAY TIME", 25);		

		
		// ** Play Time Text UI
		pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::UI_TEXT);
		pPlayTimeTextUI = ObjectManager::GetInstance()->NewObject(eObjectKey::UI);
		pPlayTimeTextUI->SetPosition(
			pOwner->GetPosition().x + (pOwner->GetScale().x * 0.07f),
			pOwner->GetPosition().y + (pOwner->GetScale().y * 0.24f));
		pPlayTimeTextUI->SetScale(pPlayTimeNameTextUI->GetScale());
		pPlayTimeTextUI->SetBridge(pBridge);
		static_cast<TextUI*>(pBridge)->SetText(
			GameDataManager::GetInstance()->GetPlayTimeStrFormat(), 25);

		// ** Score Name Text UI
		pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::UI_TEXT);
		pScoreNameTextUI = ObjectManager::GetInstance()->NewObject(eObjectKey::UI);
		pScoreNameTextUI->SetPosition(
			pOwner->GetPosition().x - (pOwner->GetScale().x * 0.18f),
			pOwner->GetPosition().y + (pOwner->GetScale().y * 0.31f));
		pScoreNameTextUI->SetScale(100.0f, 50.0f);
		pScoreNameTextUI->SetBridge(pBridge);
		static_cast<TextUI*>(pBridge)->SetText("SCORE", 25);

		// ** Score UI
		pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::UI_SCORE);
		pScoreUI = ObjectManager::GetInstance()->NewObject(eObjectKey::UI);
		pScoreUI->SetPosition(
			pOwner->GetPosition().x + (pOwner->GetScale().x * 0.05f),
			pOwner->GetPosition().y + (pOwner->GetScale().y * 0.29f));
		pScoreUI->SetScale(80.0f, 40.0f);
		pScoreUI->SetBridge(pBridge);

		// ** Press Enter Text UI
		pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::UI_TEXT);
		pScoreNameTextUI = ObjectManager::GetInstance()->NewObject(eObjectKey::UI);
		pScoreNameTextUI->SetPosition(
			pOwner->GetPosition().x - (pOwner->GetScale().x * 0.121f),
			pOwner->GetPosition().y + (pOwner->GetScale().y * 0.45f));
		pScoreNameTextUI->SetScale(40.0f, 20.0f);
		pScoreNameTextUI->SetBridge(pBridge);
		static_cast<TextUI*>(pBridge)->SetText("PRESS ENTER", 17);

		bInitializedObjects = true;
	}
	else
	{
		pPlayTimeNameTextUI = nullptr;
		pPlayTimeTextUI = nullptr;
		pScoreNameTextUI = nullptr;
		pScoreUI = nullptr;
	}
}

string GameClearUI::ConvertTimeToStrTimeFormat(ULONGLONG _time)
{
	int hour	= static_cast<int>(_time / 3600);
	int min		= static_cast<int>((_time % (ULONGLONG)3600) / 60);
	int seconds = static_cast<int>((_time % (ULONGLONG)3600) % 60);

	string hourStr	  = to_string(hour / 10)	+ to_string(hour % 10);
	string minStr	  = to_string(min / 10)		+ to_string(min % 10);
	string secondsStr = to_string(seconds / 10) + to_string(seconds % 10);

	return hourStr + ":" + minStr + ":" + secondsStr;
}