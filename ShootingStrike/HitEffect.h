#pragma once
#include "EffectBridge.h"

class HitEffect : public EffectBridge
{
public:
	typedef EffectBridge Super;

private:
	int segmentImageCount;
	int offset;
	int delay;
	ULONGLONG time;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

	virtual Bridge* Clone() override { return new HitEffect(*this); }

public:
	HitEffect();
	virtual ~HitEffect();
};

