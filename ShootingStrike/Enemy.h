#pragma once
#include "Object.h"

class Enemy : public Object
{
public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;
	virtual void OnCollision(Object* _pObject)override;

	virtual Object* Clone()override { return new Enemy(*this); }
public:
	Enemy();
	Enemy(const Transform& _rTransInfo) : Object(_rTransInfo) { }
	virtual ~Enemy();
};
