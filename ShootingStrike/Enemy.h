#pragma once
#include "Object.h"

class Enemy : public Object
{
public:
	typedef Object Super;

private:
	int HP;

	bool bSpawing;
	bool bAttacking;
	bool bTakeDamage;
	bool bDied;

	int hitScore;
	int deathScore;

	Vector3 oldPosition;

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

	// ** 죽음
	void Die();

	bool IsDead() { return bDied; }

	int GetHP() { return HP; }
	int GetHitPoint() { return hitScore; }
	int GetDeathPoint() { return deathScore; }

	void SetHP(int _HP) { HP = _HP; }
	void SetHitPoint(int _Point) { hitScore = _Point; }
	void SetDeathPoint(int _Point) { deathScore = _Point; }

private:
	// ** Stage 전장을 벗어났는지 체크
	void CheckPositionInBkgBoundary();

public:
	Enemy();
	Enemy(const Transform& _rTransInfo) : Object(_rTransInfo) { }
	virtual ~Enemy();
};
