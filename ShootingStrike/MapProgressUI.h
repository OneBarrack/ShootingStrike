#pragma once
#include "UIBridge.h"

class MapProgressUI : public UIBridge
{
public:
	typedef UIBridge Super;

private:
	Bitmap* pBkgImage;
	Bitmap* pPlayerImage;
	float mapProgressRatio;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

	virtual Bridge* Clone() override { return new MapProgressUI(*this); }

public:
	MapProgressUI();
	virtual ~MapProgressUI();
};

