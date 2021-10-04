#pragma once
#include "SpawnPatternScript.h"

class BulletSpawnPatternScript : public SpawnPatternScript
{
private:
	// ** 주체 Object
	Object* pOwner;

	// ** Spawn Pattern
	eBulletSpawnPattern spawnPattern;

	// ** Spawn Position
	Vector3 spawnPosition;

	// ** 데미지
	int damage;

	// ** Run 할 준비 되었는지
	bool bReady;
	
public:	
	// ** 초기화
	void Initialize(Object* _pOwner = nullptr);

	// ** Pattern 및 데미지 세팅
	void ReadyToSpawn(eBulletSpawnPattern _spawnPattern, Vector3 _spawnPosision, int _damage);

	// ** 실행 중인지
	bool IsRunning() { return !bReady; }

	// ** 패턴 실행
	virtual void Run() override;
	// 포지션, 디렉션, 미리 레디투스폰에서 받아야하는것?
public:
	BulletSpawnPatternScript();
	~BulletSpawnPatternScript();
};

