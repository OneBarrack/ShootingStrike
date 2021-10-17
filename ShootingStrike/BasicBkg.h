#pragma once
#include "BackgroundBridge.h"

class BasicBkg : public BackgroundBridge
{
public:
	typedef BackgroundBridge Super;

private:
	bool bPlayAnimation;
	int segmentationIndex;
	ULONGLONG time;
	int animationDelay;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

	virtual Bridge* Clone() override { return new BasicBkg(*this); }

public:
	void PlayAnimation() { bPlayAnimation = true; }
	void StopAnimation() { bPlayAnimation = false; }
	void SetAnimationDelay(int _delay) { animationDelay = _delay; }

public:
	BasicBkg();
	virtual ~BasicBkg();
};

