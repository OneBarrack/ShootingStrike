#pragma once
#include "ItemBridge.h"

class StayInPlaceItem : public ItemBridge
{
public:
	typedef ItemBridge Super;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

	virtual Bridge* Clone() override { return new StayInPlaceItem(*this); };

public:
	StayInPlaceItem();
	virtual ~StayInPlaceItem();
};



