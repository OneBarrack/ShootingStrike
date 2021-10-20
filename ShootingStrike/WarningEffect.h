#pragma once
#include "EffectBridge.h"

class WarningEffect : public EffectBridge
{
public:
	typedef EffectBridge Super;

private:
	Bitmap* pFadeBackImage;

	// ** AlphaBlend시 사용할 데이터
	BYTE alpha;
	int fadeSpeed;

	// ** Warning image가 Fade out / in 되는 cycle 횟수
	int fadeCycleCount;

	// ** Fade out / in cycle을 몇 회 진행 할것인지
	int maxFadeCycleCount;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

	virtual Bridge* Clone() override { return new WarningEffect(*this); }

public:
	WarningEffect();
	virtual ~WarningEffect();
};

