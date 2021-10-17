#pragma once
#include "SpawnPatternScript.h"

class EnemySpawnPatternScript : public SpawnPatternScript
{
private:
	// ** 준비된 패턴들을 모아놓은 List
	list<pair<Object*, eEnemySpawnPattern>> readyPatternList;

public:
	// ** 초기화
	void Initialize();

	// ** Pattern 및 데미지 세팅
	void ReadyToSpawn(Object* _pOwner, eEnemySpawnPattern _spawnPattern);

	// ** 패턴 실행
	virtual void Run() override;

private:
	// ** 오브젝트 스폰 패턴 
	virtual void Spawn() override;

	// ** 스폰 대상들에 대한 업데이트
	virtual void Update() override;

public:
	EnemySpawnPatternScript();
	~EnemySpawnPatternScript();
};

