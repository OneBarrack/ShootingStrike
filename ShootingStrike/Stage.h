#pragma once
#include "Scene.h"
#include "EnemySpawnPatternScript.h"

class Object;
class Stage : public Scene
{
private:
	int frame;
	ULONGLONG startTime;
	ULONGLONG currentTime;

	Object* pPlayer;
	Object* pStageDummyEnemy;
	Object* pBackground;
	Object* pLeftSideBackground;
	Object* pRightSideBackground;
	Object* pPlayTimeTextUI;
	Object* pScoreTextUI;
	Object* pScoreUI;
	Object* pLifeTextUI;
	Object* pLifeUI;
	Object* pGameOverUI;
	Object* pGameClearUI;
	Object* pBombTextUI;
	Object* pBombUI;
	Object* pBossAngelEnemy;
	Object* pBossEnemyProgressBar;
	Object* pMapProgress;	

	// ** 보스가 소환 되었는지
	bool bSpawnedBossEnemy;

	// ** Enemy Spawn Script
	EnemySpawnPatternScript enemyScript;

	// ** Enemy Spawn Pattern 발동 타이밍 정보
	// ** First : Map Progress Percentage, Second : eEnemySpawnPattern
	priority_queue<	
		pair<float, eEnemySpawnPattern>, 
		vector<pair<float, eEnemySpawnPattern>>,
		greater<pair<float, eEnemySpawnPattern>> > enemySpawnTimings;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

public:
	ULONGLONG GetPlayTime() { return currentTime - startTime; }

private:
	// ** 진행거리에 따른 Enemy Spawn Script List 초기 저장값 세팅
	void InitEnemySpawnPatternTimings();

	// ** Stage Start
	void Start();

public:
	Stage();
	virtual ~Stage();
};