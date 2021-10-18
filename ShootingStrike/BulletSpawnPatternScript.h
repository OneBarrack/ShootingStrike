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

	// ** N각형 Polygon pattern에서 사용될 버텍스 수
	int polygonVtxCount;

public:	
	// ** 초기화
	void Initialize();

	// ** Pattern 및 데미지 세팅
	void ReadyToSpawn(Object* _pOwner, eBulletSpawnPattern _spawnPattern, Transform _spawnTransInfo, int _damage, int _polygonVtxCount = 0);

	// ** 실행 중인지
	bool IsRunning() { return !bReady; }

	// ** 패턴 실행
	virtual void Run() override;

private:
	// ** 오브젝트 스폰 패턴 
	virtual void Spawn() override;

	// ** 스폰 대상들에 대한 업데이트
	virtual void Update() override;

public:
	BulletSpawnPatternScript();
	~BulletSpawnPatternScript();
};

