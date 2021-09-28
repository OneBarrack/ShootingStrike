#pragma once
#include "EnemyBridge.h"

class BossEnemy : public EnemyBridge
{
public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

	virtual BossEnemy* Clone()override { return new BossEnemy(*this); }

public:
	BossEnemy();
	virtual ~BossEnemy();
};

