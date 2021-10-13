#pragma once
#include "EnemyBridge.h"

class BossAngelEnemy : public EnemyBridge
{
public:
	typedef EnemyBridge Super;

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
	AnimationType animType;
	bool bLoopPlayAnim;	

	Vector3 spawnStartPos;
	Vector3 spawnDestPos;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

	virtual Bridge* Clone() override { return new BossAngelEnemy(*this); }

public:
	void PlayAnimation(AnimationType _animType, bool _bLoop);

private:
	void PlayAnimDefault(HDC _hdc, ULONGLONG& _time, int& _offset);
	void PlayAnimAttack1(HDC _hdc, ULONGLONG& _time, int& _offset);
	void PlayAnimAttack2(HDC _hdc, ULONGLONG& _time, int& _offset);
	void PlayAnimAttack3(HDC _hdc, ULONGLONG& _time, int& _offset);
	void PlayAnimEvolution(HDC _hdc, ULONGLONG& _time, int& _offset);
	void PlayAnimAttacked(HDC _hdc, ULONGLONG& _time, int& _offset);

public:
	BossAngelEnemy();
	virtual ~BossAngelEnemy();
};

