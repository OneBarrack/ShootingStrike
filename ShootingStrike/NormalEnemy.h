#pragma once
#include "EnemyBridge.h"

class NormalEnemy : public EnemyBridge
{
public:
	typedef EnemyBridge Super;

private:
	ULONGLONG bulletSpawnTime;	
	ULONGLONG animationTime;
	Vector3 imageOffset;
	Vector3 imageScale;
	int segmentationOffset;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

	virtual Bridge* Clone() override { return new NormalEnemy(*this); }

public:
	NormalEnemy();
	virtual ~NormalEnemy();
};

