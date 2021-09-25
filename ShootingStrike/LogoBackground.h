#pragma once
#include "BackgroundBridge.h"

class LogoBackground : public BackgroundBridge
{
private:
	// ** Logo Background
	Bitmap* pLogoBkgImage;
	Vector3 LogoBkgScale;
	int LoopOffset1;
	int LoopOffset2;
	int ScrollSpeed;
	bool bAttachBkg;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

private:
	// ** Draw Logo background
	void RenderLogoBkg(HDC _hdc);

public:
	LogoBackground();
	virtual ~LogoBackground();
};

