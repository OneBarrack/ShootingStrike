#pragma once
#include "Bridge.h"

class EnemyBridge : public Bridge
{
protected:
	Transform TransInfo;
	float Speed;

public:
	virtual void Initialize()PURE;
	virtual void Update()PURE;
	virtual void Render(HDC _hdc)PURE;
	virtual void Release()PURE;
public:
	EnemyBridge();
	virtual ~EnemyBridge();
};
