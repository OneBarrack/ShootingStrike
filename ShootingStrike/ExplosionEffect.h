#pragma once
#include "EffectBridge.h"

class ExplosionEffect : public EffectBridge
{
public:
	typedef EffectBridge Super;

private:
	int offset;
	int delay;
	ULONGLONG time;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

	virtual Bridge* Clone() override { return new ExplosionEffect(*this); }

public:
	ExplosionEffect();
	virtual ~ExplosionEffect();
};

