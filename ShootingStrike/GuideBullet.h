#pragma once
#include "BulletBridge.h"

class GuideBullet : public BulletBridge
{
public:
	typedef BulletBridge Super;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

	virtual Bridge* Clone()override { return new GuideBullet(*this); }

private:
	// ** 유도 미사일의 Direction 계산
	void CalcGuideDirection(Vector3 _pos, Vector3& _rDirection);

	// ** 가장 가까운 적 탐색
	Object* FindTarget(Vector3 _pos);

	void RenderBullet(HDC _hdc);

public:
	GuideBullet();
	virtual ~GuideBullet();
};

