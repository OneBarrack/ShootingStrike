#pragma once
#include "BulletBridge.h"

class GuideBullet : public BulletBridge
{
private:
	// ** Bullet
	Bitmap* pBulletImage;
	Vector3 BulletImageScale;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

private:
	// ** 유도 미사일의 Direction 계산
	void CalcGuideDirection(Vector3 _Pos, Vector3& _rDirection);

	// ** 가장 가까운 적 탐색
	Object* FindTarget(Vector3 _Pos);

	void RenderBullet(HDC _hdc);

public:
	GuideBullet();
	virtual ~GuideBullet();
};

