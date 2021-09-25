#pragma once
#include "BackgroundBridge.h"

class StageBackground : public BackgroundBridge
{
private:
	// ** Stage background
	Bitmap* pStageBkgImage;
	Vector3 StageBkgScale;
	float StageBkgOffset;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

private:
	// ** Draw Stage main background
	void RenderStageBkg(HDC _hdc);

public:
	StageBackground();
	virtual ~StageBackground();
};

