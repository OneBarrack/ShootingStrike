#pragma once
#include "BulletBridge.h"

class NormalBullet : public BulletBridge
{
public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;	

public:
	NormalBullet();
	virtual ~NormalBullet();
};

