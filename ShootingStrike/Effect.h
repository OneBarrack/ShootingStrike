#pragma once
#include "Object.h"

class Effect : public Object
{
public:
	typedef Object Super;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;
	virtual void OnCollision(Object* _pObject) override;

	virtual Object* Clone() { return new Effect(*this); };

public:
	Effect();
	Effect(const Transform& _rTransInfo) : Object(_rTransInfo) {}
	virtual ~Effect();
};

