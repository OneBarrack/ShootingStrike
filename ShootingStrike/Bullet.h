#pragma once
#include "Object.h"

class Bullet : public Object
{
public:
	typedef Object Super;

private:
	Object* pOwner;
	int Damage;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;
	virtual void OnCollision(Object* _pObject)override;

	virtual Object* Clone()override { return new Bullet(*this); }

public:
	void SetOwner(Object* _Owner) { pOwner = _Owner; }
	void SetDamage(const int _Damage) { Damage = _Damage; }	

	Object* GetOwner() { return pOwner; }
	int GetDamage() { return Damage; }

public:
	Bullet();
	Bullet(const Transform& _rTransInfo) : Object(_rTransInfo) { }
	virtual ~Bullet();
};

