#pragma once
#include "ItemBridge.h"

class GoToPlayerItem : public ItemBridge
{
public:
	typedef ItemBridge Super;

private:
	ULONGLONG guideTime;
	int guideDelayTime;

	bool bGuidePlayer;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

	virtual Bridge* Clone() override { return new GoToPlayerItem(*this); };

private:
	void CalcGuideDirectionForPlayer(Vector3 _pos, Vector3& _rDirection);

public:
	GoToPlayerItem();
	virtual ~GoToPlayerItem();
};



