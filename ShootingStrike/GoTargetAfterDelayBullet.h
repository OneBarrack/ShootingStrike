#pragma once
#include "BulletBridge.h"

class GoTargetAfterDelayBullet : public BulletBridge
{
public:
	typedef BulletBridge Super;

private:
	ULONGLONG time;
	int delay;

	// ** 타겟 방향으로 1회만 설정하기 위한 Flag
	bool bDelayOver;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

	virtual Bridge* Clone() override { return new GoTargetAfterDelayBullet(*this); }

public:
	void SetDelay(int _milliSeconds) { delay = _milliSeconds; }

private:
	bool CalcGuideDirection(Vector3 _pos, Vector3& _rDirection);
	Object* FindTarget(Vector3 _pos);

public:
	GoTargetAfterDelayBullet();
	virtual ~GoTargetAfterDelayBullet();
};

