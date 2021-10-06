#pragma once
#include "UIBridge.h"

class LifeUI : public UIBridge
{

public:
	typedef UIBridge Super;

private:
	Bitmap* pPlayerImage;
	int life;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

	virtual Bridge* Clone() override { return new LifeUI(*this); }

public:
	LifeUI();
	virtual ~LifeUI();
};

