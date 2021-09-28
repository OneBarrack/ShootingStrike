#pragma once
#include "Bridge.h"

class BackgroundBridge : public Bridge
{
public:
	virtual void Initialize()PURE;
	virtual void Update()PURE;
	virtual void Render(HDC _hdc)PURE;
	virtual void Release()PURE;

	virtual Bridge* Clone()PURE;

public:
	BackgroundBridge();
	virtual ~BackgroundBridge();
};

