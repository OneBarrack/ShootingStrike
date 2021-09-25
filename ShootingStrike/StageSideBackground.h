#pragma once
#include "BackgroundBridge.h"

class StageSideBackground : public BackgroundBridge
{
private:
	// ** Stage side background
	Bitmap* pStageSideBkgImage;
	Vector3 SideBkgScale;
	float SideBkgOffset;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

private:
	// ** Draw Stage side background
	void RenderStageSideBkg(HDC _hdc);

public:
	StageSideBackground();
	virtual ~StageSideBackground();
};

