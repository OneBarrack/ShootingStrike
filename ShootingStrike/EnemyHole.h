#pragma once
#include "Object.h"

class EnemyHole : public Object
{
private:
	Object* EnemyMole;
public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;
	virtual void OnCollision(Object* _pObject)override;

	virtual Object* Clone()override { return new EnemyHole(*this); }
public:
	EnemyHole();
	EnemyHole(const Transform& _rTransInfo) : Object(_rTransInfo) { }
	virtual ~EnemyHole();
};
