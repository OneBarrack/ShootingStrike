#pragma once
#include "Bridge.h"

class BackgroundBridge : public Bridge
{
protected:
	Bitmap* pImage;
	Transform TransInfo;
	float Speed;

public:
	virtual void Initialize()PURE;
	virtual void Update()PURE;
	virtual void Render(HDC _hdc)PURE;
	virtual void Release()PURE;

	virtual Bridge* Clone()PURE;

public:
	// ** Owner의 데이터를 받아옴
	virtual void ReceiveInfoFromOwner() override;

	// ** Owner로 가공된 데이터 전달
	virtual void SendInfoToOwner() override;

public:
	BackgroundBridge();
	virtual ~BackgroundBridge();
};

