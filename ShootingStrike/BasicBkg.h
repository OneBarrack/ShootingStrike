#pragma once
#include "BackgroundBridge.h"

class BasicBkg : public BackgroundBridge
{
public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

	virtual Bridge* Clone()override { return new BasicBkg(*this); }

public:
	BasicBkg();
	virtual ~BasicBkg();
};

