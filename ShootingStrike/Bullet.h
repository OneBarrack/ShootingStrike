#pragma once
#include "Object.h"

class Bullet : public Object
{
private:
	Object* Target;
public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;
	virtual void OnCollision(Object* _pObject)override;

	virtual Object* Clone()override { return new Bullet(*this); }
public:
	void SetTarget(Object* _Target) { Target = _Target; }

private:
	bool IsOutOfScreen();

public:
	Bullet();
	Bullet(const Transform& _rTransInfo) : Object(_rTransInfo) { }
	virtual ~Bullet();
};

