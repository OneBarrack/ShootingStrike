#pragma once
#include "Bridge.h"
#include "BulletSpawnPatternScript.h"

class EnemyBridge : public Bridge
{
protected:
	BulletSpawnPatternScript bulletScript;
	Bitmap* pImage;
	Transform transInfo;
	float speed;

public:
	virtual void Initialize() PURE;
	virtual void Update() PURE;
	virtual void Render(HDC _hdc) PURE;
	virtual void Release() PURE;

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
