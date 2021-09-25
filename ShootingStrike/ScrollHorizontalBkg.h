#pragma once
#include "BackgroundBridge.h"

class ScrollHorizontalBkg : public BackgroundBridge
{
private:
	bool bLoopScroll;
	int LoopOffset1;
	int LoopOffset2;
	bool bAttachBkg;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

	bool IsLoopScroll() { return bLoopScroll; }
	void SetLoopScroll(bool _bLoopScroll) { bLoopScroll = _bLoopScroll; }

public:
	ScrollHorizontalBkg();
	virtual ~ScrollHorizontalBkg();
};

