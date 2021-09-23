#pragma once
#include "Object.h"

class Bullet : public Object
{
private:
	Object* Owner;
	int Damage;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;
	virtual void OnCollision(Object* _pObject)override;

	virtual Object* Clone()override { return new Bullet(*this); }

public:
	void SetOwner(Object* _Owner) { Owner = _Owner; }
	void SetDamage(const int _Damage) { Damage = _Damage; }
	void SetDirection(Vector3 _Direction) { TransInfo.Direction = _Direction; }

	Object* GetOwner() { return Owner; }
	int GetDamage() { return Damage; }

private:
	bool IsOutOfScreen();

public:
	Bullet();
	Bullet(const Transform& _rTransInfo) : Object(_rTransInfo) { }
	virtual ~Bullet();
};

