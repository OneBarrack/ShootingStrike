#pragma once
#include "BulletBridge.h"

class GuideBullet : public BulletBridge
{
public:
	typedef BulletBridge Super;

private:
	// ** 가장 가까운 오브젝트와의 거리
	float distToTarget;

	// ** 무한 유도 할 것인지. false 일 시 방향은 타겟쪽으로 1회 향한 후 고정된다.
	bool bLoopGuide;
	bool bGuideEnd;

	// ** Delay가 있는지
	bool hasDelay;
	ULONGLONG time;
	int delay;;
	
	// ** Delay 이후 필요한 방향, 속도, 가속도
	Vector3 directionAfterDelay;
	float speedAfterDelay;
	float accelerationAfterDelay;
	float maxSpeed;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

	virtual Bridge* Clone()override { return new GuideBullet(*this); }

public:
	void SetLoopGuide(bool _bLoopGuide);
	void SetDelay(Vector3 _directionAfterDelay, float _speed = 0.0f, float _maxSpeed = 10.0f, float _acceleration = 0.0f, int _delay = 0);

	// ** 가장 가까운 오브젝트와의 거리 반환
	float GetDistToTarget() { return distToTarget; }

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

