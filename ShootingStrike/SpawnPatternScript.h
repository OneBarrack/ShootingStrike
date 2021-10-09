#pragma once
#include "Headers.h"
#include "Object.h"

class SpawnPatternScript
{
protected:
	// ** 오브젝트 스폰 패턴 
	virtual void Spawn() PURE;

	// ** 스폰 대상들에 대한 업데이트
	virtual void Update() PURE;

public:
	// ** 패턴 실행
	virtual void Run() PURE;


public:
	SpawnPatternScript() {}
	~SpawnPatternScript() {}
};

