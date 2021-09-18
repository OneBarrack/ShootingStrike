#pragma once
#include "BackgroundBridge.h"

class StageBackground : public BackgroundBridge
{
private:
	Vector3 StageBkgScale;
	Vector3 SideBkgScale;
	float StageBkgOffset;
	float SideBkgOffset;

public:
	virtual void Initialize()override;
	virtual void Update(Transform& _rTransInfo)override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;
public:
	StageBackground();
	virtual ~StageBackground();
};

