#pragma once
#include "EnemyBridge.h"

class GoAndSpinEnemy : public EnemyBridge
{
	enum class eSpinDirection
	{
		LEFT,
		RIGHT
	};

public:
	typedef EnemyBridge Super;

private:
	ULONGLONG time;

	// ** Spin 진행 방향
	eSpinDirection spinDirection;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

	virtual Bridge* Clone() override { return new GoAndSpinEnemy(*this); }

public:
	void LeftSpin() { spinDirection = eSpinDirection::LEFT; }
	void RightSpin() { spinDirection = eSpinDirection::RIGHT; }

public:
	GoAndSpinEnemy();
	virtual ~GoAndSpinEnemy();
};

