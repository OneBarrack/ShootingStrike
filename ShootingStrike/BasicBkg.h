#pragma once
#include "BackgroundBridge.h"

class BasicBkg : public BackgroundBridge
{
public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

public:
	BasicBkg();
	virtual ~BasicBkg();
};

