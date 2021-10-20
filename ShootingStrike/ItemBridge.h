#pragma once
#include "Bridge.h"

class ItemBridge : public Bridge
{
protected:
	Bitmap* pImage;
	Transform transInfo;
	Transform collider;
	float speed;
	float acceleration;

	eItemType itemType;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

	virtual Bridge* Clone() PURE;

public:
	// ** Owner의 데이터를 받아옴
	virtual void ReceiveInfoFromOwner() override;

	// ** Owner로 가공된 데이터 전달
	virtual void SendInfoToOwner() override;

public:
	ItemBridge();
	virtual ~ItemBridge();
};
