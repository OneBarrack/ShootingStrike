#pragma once
#include "EnemyBridge.h"

class BossAngelEnemy : public EnemyBridge
{
public:
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
	bool bLoopPlayAnim;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

	virtual BossAngelEnemy* Clone()override { return new BossAngelEnemy(*this); }

public:
	void PlayAnimation(AnimationType _AnimType, bool _bLoop);

private:
	void PlayAnimDefault(HDC _hdc, ULONGLONG& _Time, int& _Offset);
	void PlayAnimAttack1(HDC _hdc, ULONGLONG& _Time, int& _Offset);
	void PlayAnimAttack2(HDC _hdc, ULONGLONG& _Time, int& _Offset);
	void PlayAnimAttack3(HDC _hdc, ULONGLONG& _Time, int& _Offset);
	void PlayAnimEvolution(HDC _hdc, ULONGLONG& _Time, int& _Offset);
	void PlayAnimAttacked(HDC _hdc, ULONGLONG& _Time, int& _Offset);

public:
	BossAngelEnemy();
	virtual ~BossAngelEnemy();
};

