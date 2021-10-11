#pragma once
#include "EnemyBridge.h"

class NormalGoEnemy : public EnemyBridge
{
public:
	typedef EnemyBridge Super;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

	virtual Bridge* Clone() override { return new NormalGoEnemy(*this); }

public:
	NormalGoEnemy();
	virtual ~NormalGoEnemy();
};

