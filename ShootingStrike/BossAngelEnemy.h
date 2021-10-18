#pragma once
#include "EnemyBridge.h"

class Background;
class BossAngelEnemy : public EnemyBridge
{
	enum class eActionState
	{
		READY,
		WORKING,
		END,
	};

	enum class eActionType
	{
		MOVE_SPAWN_POS				,
		FIRE_FALLDOWN_BACK_AND_FORTH,
		FIRE_TRIANGLE				,
		FIRE_DIAMOND				,
		FIRE_MULTI_SPIN				,
	};

public:
	typedef EnemyBridge Super;

public:
	enum class eBossAnimationType
	{
		DEFAULT,
		ATTACK1,
		ATTACK2,
		ATTACK3,
		EVOLUTION,
		ATTACKED,
	};

private:
	// ** 스폰된 백그라운드
	Background* pBackground;

	int curPhase;

	eBossAnimationType animType;
	bool bLoopPlayAnim;	

	Vector3 spawnStartPos;
	Vector3 spawnDestPos;

	ULONGLONG prevActionCompleteTime;
	// ** Action Script - first : actionType, second : delay
	queue<pair<eActionType, float>> actionInfos;
	eActionState actionState;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

	virtual Bridge* Clone() override { return new BossAngelEnemy(*this); }

public:
	void PlayAnimation(eBossAnimationType _animType, bool _bLoop);
	int GetPhase() { return curPhase; }

private:
	void PlayAnimDefault(HDC _hdc, ULONGLONG& _time, int& _offset);
	void PlayAnimAttack1(HDC _hdc, ULONGLONG& _time, int& _offset);
	void PlayAnimAttack2(HDC _hdc, ULONGLONG& _time, int& _offset);
	void PlayAnimAttack3(HDC _hdc, ULONGLONG& _time, int& _offset);
	void PlayAnimEvolution(HDC _hdc, ULONGLONG& _time, int& _offset);
	void PlayAnimAttacked(HDC _hdc, ULONGLONG& _time, int& _offset);

	// ** ActionInfo 리셋
	void InitActionInfo();
	void Action(eActionType _bossActionType);

	// ** Phase 체크
	void CheckPhase();

public:
	BossAngelEnemy();
	virtual ~BossAngelEnemy();
};

