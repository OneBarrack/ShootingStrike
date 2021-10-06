#include "GameDataManager.h"
#include "ObjectManager.h"
#include "Player.h"

GameDataManager* GameDataManager::pInstance = nullptr;

GameDataManager::GameDataManager()
	: playerLife(0)
	, score(0)
	, FPS(0)
{
}

GameDataManager::~GameDataManager()
{
}

void GameDataManager::Initialize()
{
	playerLife = 0;
	score = 0;
	FPS = 0;
}

void GameDataManager::Update()
{
	playerLife = static_cast<Player*>(ObjectManager::GetInstance()->GetPlayer())->GetLife();
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
	static int frame = 0;

	++frame;

	if ( Time + 1000 < GetTickCount64() )
	{
		FPS = frame;
		Time = GetTickCount64();
		frame = 0;
	}
}
