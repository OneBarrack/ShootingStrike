#pragma once
#include "UIBridge.h"

class BombUI : public UIBridge
{

public:
	typedef UIBridge Super;

private:
	Bitmap* pItemImage;
	int bombCount;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

	virtual Bridge* Clone() override { return new BombUI(*this); }

public:
	BombUI();
	virtual ~BombUI();
};

