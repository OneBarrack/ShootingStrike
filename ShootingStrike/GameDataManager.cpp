#include "GameDataManager.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Background.h"

GameDataManager* GameDataManager::pInstance = nullptr;

GameDataManager::GameDataManager()
	: playerLife(0)
	, score(0)
	, FPS(0)
	, frame(0)
	, mapProgressRatio(0.0f)
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
}

void GameDataManager::Update()
{
	++frame;
	
	Player* pPlayer = static_cast<Player*>(ObjectManager::GetInstance()->GetPlayer());
	playerPos = pPlayer->GetPosition();
	playerLife = pPlayer->GetLife();
	
	Object* pBkgObject = ObjectManager::GetInstance()->FindObjectWithTag(eTagName::STAGE_MAIN_BKG);
	if ( pBkgObject )
	mapProgressRatio = static_cast<Background*>(pBkgObject)->GetMapProgressRatio();
		
	CalcFPS();
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
