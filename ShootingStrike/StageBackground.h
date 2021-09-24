#pragma once
#include "BackgroundBridge.h"

class StageBackground : public BackgroundBridge
{
private:
	// ** 좌우 Border line을 그리기 위한 배경
	Bitmap* pBkgImageForBorderLine;

	// ** Stage background
	Bitmap* pStageBkgImage;
	Vector3 StageBkgScale;
	float StageBkgOffset;

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
	// ** Draw Background for borderLine (센터 좌우 검은 경계선을 나타내기 위해 배경에 그려둠)
	void RenderBkgForBorderLine(HDC _hdc);
	
	// ** Draw Stage main background
	void RenderStageBkg(HDC _hdc);

	// ** Draw Stage side background
	void RenderStageSideBkg(HDC _hdc);

public:
	StageBackground();
	virtual ~StageBackground();
};

