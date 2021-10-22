#include "GameDataManager.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Background.h"
#include "SceneManager.h"
#include "Stage.h"

GameDataManager* GameDataManager::pInstance = nullptr;

GameDataManager::GameDataManager()
	: playerLife(0)
	, score(0)
	, FPS(0)
	, frame(0)
	, mapProgressRatio(0.0f)
	, playTime(0)
{
}

GameDataManager::~GameDataManager()
{
}

void GameDataManager::Initialize()
{
	playerPos = Vector3();
	playerLife = 0;
	score = 0;
	FPS = 0;
	frame = 0;
	mapProgressRatio = 0.0f;
	playTime = 0;
}

void GameDataManager::Update()
{
	++frame;
	
	Object* pPlayer = ObjectManager::GetInstance()->GetPlayer();
	if ( pPlayer )
	{
		playerPos = pPlayer->GetPosition();
		playerLife = static_cast<Player*>(pPlayer)->GetLife();
	}

	Object* pBkgObject = ObjectManager::GetInstance()->FindObjectWithTag(eTagName::STAGE_MAIN_BKG);
	if ( pBkgObject )
	{
		mapProgressRatio = static_cast<Background*>(pBkgObject)->GetMapProgressRatio();
	}

	if ( SceneManager::GetInstance()->GetCurrentSceneID() == eSCENEID::STAGE )
	{
		playTime = static_cast<Stage*>(SceneManager::GetInstance()->GetScene())->GetPlayTime();
	}
		
	CalcFPS();
}

string GameDataManager::GetPlayTimeStrFormat()
{
	ULONGLONG timeSeconds = playTime / 1000;

	int hour = static_cast<int>(timeSeconds / 3600);
	int min = static_cast<int>((timeSeconds % (ULONGLONG)3600) / 60);
	int seconds = static_cast<int>((timeSeconds % (ULONGLONG)3600) % 60);

	string hourStr = to_string(hour / 10) + to_string(hour % 10);
	string minStr = to_string(min / 10) + to_string(min % 10);
	string secondsStr = to_string(seconds / 10) + to_string(seconds % 10);

	return hourStr + ":" + minStr + ":" + secondsStr;
}

void GameDataManager::AddScore(int _score)
{
	// ** INT 최대 값을 넘긴다면 INT_MAX로 고정
	if ( (ULONGLONG)score + _score > INT_MAX )
		score = INT_MAX;
	else
		score += _score;
}

void GameDataManager::CalcFPS()
{
	// ** FPS 계산
	static ULONGLONG Time = GetTickCount64();
	static int fps = 0;

	++fps;

	if ( Time + 1000 < GetTickCount64() )
	{
		FPS = fps;
		Time = GetTickCount64();
		fps = 0;
	}
}
