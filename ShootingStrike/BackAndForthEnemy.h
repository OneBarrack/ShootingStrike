#pragma once
#include "EnemyBridge.h"

class BackAndForthEnemy : public EnemyBridge
{
	enum class eBackAndForthDirection
	{
		LEFT,
		RIGHT
	};

public:
	typedef EnemyBridge Super;

private:
	ULONGLONG time;

	// ** 목적지 중간 위치에 도달했는지
	int angle;

	// ** 진행 방향의 수직 벡터
	Vector3 perpendicularDirection;
	bool bFindPerpendicularDirection;

	// ** 최초 진행 방향
	eBackAndForthDirection startDirection;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

	virtual Bridge* Clone() override { return new BackAndForthEnemy(*this); }

public:
	void LeftSpin() { startDirection = eBackAndForthDirection::LEFT; }
	void RightSpin() { startDirection = eBackAndForthDirection::RIGHT; }

public:
	BackAndForthEnemy();
	virtual ~BackAndForthEnemy();
};

