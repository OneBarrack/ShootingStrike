#pragma once
#include "BackgroundBridge.h"

class ScrollVerticalBkg : public BackgroundBridge
{
private:
	bool bLoopScroll;
	float StageBkgOffset;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

	bool IsLoopScroll() { return bLoopScroll; }
	void SetLoopScroll(bool _bLoopScroll) { bLoopScroll = _bLoopScroll;	}

public:
	ScrollVerticalBkg();
	virtual ~ScrollVerticalBkg();
};

