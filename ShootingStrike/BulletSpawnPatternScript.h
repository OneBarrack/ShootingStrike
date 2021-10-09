#pragma once
#include "SpawnPatternScript.h"

class BulletSpawnPatternScript : public SpawnPatternScript
{
private:
	// ** 주체 Object
	Object* pOwner;

	// ** Spawn Pattern
	eBulletSpawnPattern spawnPattern;

	// ** Spawn Transform
	Transform spawnTransInfo;

	// ** 데미지
	int damage;

	// ** Run 할 준비 되었는지
	bool bReady;

public:	
	// ** 초기화
	void Initialize();

	// ** Pattern 및 데미지 세팅
	void ReadyToSpawn(Object* _pOwner, eBulletSpawnPattern _spawnPattern, Transform _spawnTransInfo, int _damage);

	// ** 실행 중인지
	bool IsRunning() { return !bReady; }

	// ** 패턴 실행
	virtual void Run() override;
	// 포지션, 디렉션, 미리 레디투스폰에서 받아야하는것?

private:
	// ** 오브젝트 스폰 패턴 
	virtual void Spawn() override;

	// ** 스폰 대상들에 대한 업데이트
	virtual void Update() override;

public:
	BulletSpawnPatternScript();
	~BulletSpawnPatternScript();
};

