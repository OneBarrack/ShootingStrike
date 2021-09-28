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

	int HitPoint;
	int DeathPoint;
	int Frame;

	Vector3 OldPosition;

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
	bool IsDead() { return bDied; }
	void Die() { bDied = true; };

	int GetHP() { return HP; }
	int GetHitPoint() { return HitPoint; }
	int GetDeathPoint() { return DeathPoint; }

	void SetHP(int _HP) { HP = _HP; }
	void SetHitPoint(int _Point) { HitPoint = _Point; }
	void SetDeathPoint(int _Point) { DeathPoint = _Point; }

public:
	Enemy();
	Enemy(const Transform& _rTransInfo) : Object(_rTransInfo) { }
	virtual ~Enemy();
};
