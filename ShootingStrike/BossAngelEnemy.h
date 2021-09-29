#pragma once
#include "EnemyBridge.h"

class BossAngelEnemy : public EnemyBridge
{
	enum class AnimationType
	{
		DEFAULT,
		ATTACK1,
		ATTACK2,
		ATTACK3,
		EVOLUTION,
		ATTACKED,
	};

private:
	AnimationType AnimType;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

	virtual BossAngelEnemy* Clone()override { return new BossAngelEnemy(*this); }

private:
	void PlayAnimDefault(HDC _hdc);
	void PlayAnimAttack1(HDC _hdc);
	void PlayAnimAttack2(HDC _hdc);
	void PlayAnimAttack3(HDC _hdc);
	void PlayAnimEvolution(HDC _hdc);

public:
	BossAngelEnemy();
	virtual ~BossAngelEnemy();
};

