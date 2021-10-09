#pragma once
#include "BulletBridge.h"

class SpreadAfterDelayBullet : public BulletBridge
{
public:
	typedef BulletBridge Super;

private:
	ULONGLONG time;
	int delay;
	bool bDelayOver;

	// ** 퍼뜨리는 동작 횟수
	int spreadCount;
	
	// ** 퍼뜨릴 때 발생시킬 Bullet 수
	int bulletCount;

	// ** 퍼뜨려지는 Bullet 간 간격
	int intervalAngle;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

	virtual Bridge* Clone() override { return new SpreadAfterDelayBullet(*this); }

public:
	void SetDelay(int _milliSeconds) { delay = _milliSeconds; }
	void SetSpreadCount(int _spreadCount) { spreadCount = _spreadCount; }
	void SetBulletCount(int _bulletCount) { bulletCount = _bulletCount; }
	void SetIntervalAngle(int _intervalAngle) { intervalAngle = _intervalAngle; }

public:
	SpreadAfterDelayBullet();
	virtual ~SpreadAfterDelayBullet();
};

