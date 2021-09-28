#include "GameDataManager.h"

GameDataManager* GameDataManager::Instance = nullptr;

GameDataManager::GameDataManager()
	: Score(0)
	, Time(0)
	, Frame(0)
	, FPS(0)
{
}

GameDataManager::~GameDataManager()
{
}

void GameDataManager::Initialize()
{
	Score = 0;
	Frame = 0;
	FPS = 0;
	Time = GetTickCount64();
}

void GameDataManager::Update()
{
	++Frame;

	CalcFPS();
}

void GameDataManager::AddScore(int _Score)
{
	// ** INT 최대 값을 넘긴다면 INT_MAX로 고정
	if ( (ULONGLONG)Score + _Score > INT_MAX )
		Score = INT_MAX;
	else
		Score += _Score;
}

void GameDataManager::CalcFPS()
{
	if ( Time + 1000 < GetTickCount64() )
	{
		FPS = Frame;
		Time = GetTickCount64();
		Frame = 0;
	}
}
