#pragma once
#include "Object.h"

class HammerEffect : public Object
{
private:
	int Frame;

	ULONGLONG Time;
public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;
	virtual void OnCollision(Object* _pObject)override;

	virtual Object* Clone()override { return new HammerEffect(*this); }
public:
	HammerEffect();
	HammerEffect(const Transform& _rTransInfo) : Object(_rTransInfo) { }
	virtual ~HammerEffect();
};
