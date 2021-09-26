#pragma once
#include "Bridge.h"

class BulletBridge : public Bridge
{
protected:
	Transform TransInfo;
	float Speed;

public:
	virtual void Initialize()PURE;
	virtual void Update()PURE;
	virtual void Render(HDC _hdc)PURE;
	virtual void Release()PURE;

	// ** Owner의 데이터를 받아옴
	virtual void ReceiveInfo();

	// ** Owner로 가공된 데이터 전달
	virtual void SendInfo();

public:
	BulletBridge();
	virtual ~BulletBridge();
};

