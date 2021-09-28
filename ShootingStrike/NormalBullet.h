#pragma once
#include "BulletBridge.h"

class NormalBullet : public BulletBridge
{
public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;	

	virtual Bridge* Clone()override { return new NormalBullet(*this); }

public:
	NormalBullet();
	virtual ~NormalBullet();
};

