#pragma once
#include "UIBridge.h"

class ProgressBarUI : public UIBridge
{
public:
	typedef UIBridge Super;

private:
	Bitmap* pProgressBarImage;

	// ** 표시할 값
	int value;

	// ** 표시할 값의 최대치
	int maxValue;

	float valueRatio;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

	virtual Bridge* Clone() override { return new ProgressBarUI(*this); }

public:
	void SetValue(int _value, int _maxValue);

public:
	ProgressBarUI();
	virtual ~ProgressBarUI();
};

