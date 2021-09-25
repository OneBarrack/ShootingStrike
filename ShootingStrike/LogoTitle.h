#pragma once
#include "BackgroundBridge.h"

class LogoTitle : public BackgroundBridge
{
private:
	// ** Logo
	Bitmap* pLogoImage;
	Vector3 LogoPosition;
	Vector3 LogoScale;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

private:
	// ** Draw Logo
	void RenderLogo(HDC _hdc);

public:
	LogoTitle();
	virtual ~LogoTitle();
};

