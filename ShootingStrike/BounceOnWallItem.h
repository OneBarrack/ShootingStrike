#pragma once
#include "ItemBridge.h"

class BounceOnWallItem : public ItemBridge
{
public:
	typedef ItemBridge Super;

private:
	// ** item의 진행 방향
	Vector3 itemDirection;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

	virtual Bridge* Clone() override { return new BounceOnWallItem(*this); };

private:
	// ** Stage Map 외곽에 튕겨질 때의 방향 설정
	void CalcDirectionForBounceOnWall(Transform& _transInfo);

public:
	BounceOnWallItem();
	virtual ~BounceOnWallItem();
};



