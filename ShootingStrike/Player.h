#pragma once
#include "Object.h"
#include "BulletSpawnPatternScript.h"

class Player : public Object
{
public:
	typedef Object Super;

private:
	BulletSpawnPatternScript bulletScript;

	int damage;
	int life;
	int maxLife;
	int power;
	int maxPower;

	// ** 스폰중인지
	bool isSpawing;

	// ** 리스폰인지
	bool bReSpawn; 

	// ** 죽었는지
	bool isDied;

	// ** 무적인지
	bool isInvicible;

	// ** 키 입력이 막혔는지
	bool bCantAccessInput;

	Vector3 oldPosition;

	// ** 스폰 시 딜레이 Timer
	ULONGLONG cantAccessInputTimer;
	int cantAccessInputDurationTime;

	// ** 무적 Timer
	ULONGLONG invincibleTimer;
	int invicibleDurationTime;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;	
	virtual void OnCollision(Object* _pObject) override;

	virtual Object* Clone() override { return new Player(*this); }

public:
	// ** 무적 상태인지
	bool IsInvicible() { return isInvicible; }

	// ** Life 반환
	int GetLife() { return life; }

	// ** Power,Life Up / Down
	void PowerUp(bool _bMax = false);
	void PowerDown(bool _bMin = false);
	void LifeUp(bool _bMax = false);
	void LifeDown(bool _bMin = false);

	// ** 미사일 발사
	void Fire(int _power, int _damage);

	// ** 데미지를 입힘
	void ApplyDamage(Object* _pTarget, int _damage);

	// ** 데미지를 받음
	void TakeDamage(int _damage);

	// ** Spawn
	void Spawn();

	// ** ReSpawn
	void ReSpawn();

	// ** 죽음
	void Die();

private:
	// ** 현재 플레이어 상태 체크
	void CheckStatus();

	// ** Stage 전장을 벗어났는지 체크
	void CheckPositionInBkgBoundary();

	// ** 플레이어의 캐릭터가 생성되는 애니메이션 동작. 
	// ** 발생조건 : 최초 스타트 / 죽은 후 다시 살아나는 상황
	void RenderSpawn(HDC _hdc);

	// ** 플레이어의 이동방향에 따른 기체 애니메이션 동작. 
	void RenderPlayer(HDC _hdc);

public:
	Player();
	Player(const Transform& _rTransInfo) : Object(_rTransInfo) { }
	virtual ~Player();
};

