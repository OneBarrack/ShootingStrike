#pragma once
#include "Object.h"

class Enemy : public Object
{
public:
	typedef Object Super;

private:
	int maxHP;
	int HP;	

	bool bSpawing;
	bool bAttacking;
	bool bTakeDamage;
	bool bDied;

	int hitScore;
	int deathScore;

	Vector3 oldPosition;

	// ** 스폰중인지
	bool isSpawing;

	// ** 주기적 Bullet 발사 간격
	int fireBulletIntervalTime;

	// ** 목적지
	Vector3 destPosition;

	// ** 목적지가 변경되었는지
	bool bChangedDestPos;

	// ** 목적지에서 멈추어야 하는지
	bool bStopAtDest;

	// ** 목적지에 도달 했는지
	bool bArrivedToDest;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;
	virtual void OnCollision(Object* _pObject)override;

	virtual Object* Clone()override { return new Enemy(*this); }

public:
	// ** 미사일 발사
	void Fire();

	// ** 데미지를 입힘
	void ApplyDamage(Object* _pTarget, int _Damage);

	// ** 데미지를 받음
	void TakeDamage(int _Damage);

	// ** 스폰
	void Spawn(); 

	// ** 죽음
	void Die();

	bool IsDead() { return bDied; }
	bool IsSpawning() { return isSpawing; }
	int GetMaxHP() { return maxHP; }
	int GetHP() { return HP; }
	int GetHitPoint() { return hitScore; }
	int GetDeathPoint() { return deathScore; }
	int GetFireBulletIntervalTime() { return fireBulletIntervalTime; }
	Vector3 GetDestPosition() { return destPosition; }
	bool GetChangedDestPos() { return bChangedDestPos; }
	bool GetStopAtDest() { return bStopAtDest; }
	bool GetArrivedToDest() { return bArrivedToDest; }

	void SetMaxHP(int _maxHP) { maxHP = _maxHP; }
	void SetHP(int _HP) { HP = _HP; }
	void SetHitPoint(int _point) { hitScore = _point; }
	void SetDeathPoint(int _point) { deathScore = _point; }
	void SetFireBulletIntervalTime(int _time) { fireBulletIntervalTime = _time; }
	void SetDestPosition(Vector3 _pos) { destPosition = _pos; bChangedDestPos = true; }
	void SetChangedDestPos(bool _bChanged) { bChangedDestPos = _bChanged; }
	void SetStopAtDest(bool _stopAtDest) { bStopAtDest = _stopAtDest; }
	void SetArrivedToDest(bool _arrivedToDest) { bArrivedToDest = _arrivedToDest; }
	void SetSpawnStatus(bool _isSpawing) { isSpawing = _isSpawing; }

private:
	// ** Stage 전장을 벗어났는지 체크
	void CheckPositionInBkgBoundary();

public:
	Enemy();
	Enemy(const Transform& _rTransInfo) : Object(_rTransInfo) { }
	virtual ~Enemy();
};
