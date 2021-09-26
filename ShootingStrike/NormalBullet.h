#pragma once
#include "BulletBridge.h"

class NormalBullet : public BulletBridge
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
	void RenderBullet(HDC _hdc);

public:
	NormalBullet();
	virtual ~NormalBullet();
};

