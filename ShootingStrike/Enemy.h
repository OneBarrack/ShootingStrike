#pragma once
#include "Object.h"

class Enemy : public Object
{
public:
	typedef Object Super;

private:
	Bitmap* pEnemyImage;

	int HP;

	bool bSpawing;
	bool bAttacking;
	bool bTakeDamage;
	bool bDied;

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
	void Die() { bDied = true; };

public:
	Enemy();
	Enemy(const Transform& _rTransInfo) : Object(_rTransInfo) { }
	virtual ~Enemy();
};
