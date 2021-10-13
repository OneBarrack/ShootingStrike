#pragma once
#include "Bridge.h"
#include "BulletSpawnPatternScript.h"

class EnemyBridge : public Bridge
{
protected:
	Bitmap* pImage;
	Transform transInfo;
	Transform collider;
	float speed;
	float acceleration;
	BulletSpawnPatternScript bulletScript;
	
	// ** 스폰중인지
	bool isSpawing;

	// ** 주기적 Bullet 발사 간격
	int fireBulletIntervalTime;

	// ** 목적지
	Vector3 destPosition;

	// ** 목적지가 변경되었는지
	bool bChangedDestPos;

	// ** 목적지에서 멈추어야 하는지
	bool bStopAtDest;

	// ** 목적지에 도달 했는지
	bool bArrivedToDest;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

	virtual Bridge* Clone() PURE;

public:
	// ** Owner의 데이터를 받아옴
	virtual void ReceiveInfoFromOwner() override;

	// ** Owner로 가공된 데이터 전달
	virtual void SendInfoToOwner() override;

public:
	EnemyBridge();
	virtual ~EnemyBridge();
};
