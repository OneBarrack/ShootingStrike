#pragma once
#include "Object.h"

class Enemy : public Object
{
	enum class eMoveState
	{
		READY	,
		MOVING	,
		END		,
	};

	enum class eMoveType
	{
		MOVE_TO						,
		SPIN_LEFT_FOR_LOOP			,
		SPIN_LEFT					,
		SPIN_RIGHT_FOR_LOOP			,
		SPIN_RIGHT					,
		BACK_AND_FORTH_LEFT			,
		BACK_AND_FORTH_RIGHT		,
	};

public:
	typedef Object Super;

private:
	eEnemyType enemyType;
	eItemType dropItemType;

	int maxHP;
	int HP;	
	
	int hitScore;
	int deathScore;

	Vector3 oldPosition;

	// ** 스폰중인지
	bool isSpawing;

	// ** 공격 중인지
	bool isAttacking;

	// ** 공격 당했는지
	bool isTakeDamage;

	// ** 죽었는지
	bool isDied;

	// ** 주기적 Bullet 발사 간격
	int fireBulletIntervalTime;

	// ** 목적지
	Vector3 destPosition;

	// ** Move Info
	queue<pair<eMoveType, Vector3>> moveInfos;
	eMoveState moveState;

	// ** Move Spin 시 적용된 degree값의 합
	float totalDegreeForSpin;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;
	virtual void OnCollision(Object* _pObject)override;

	virtual Object* Clone()override { return new Enemy(*this); }

public:
	// ** 미사일 발사
	void Fire();

	// ** 데미지를 입힘
	void ApplyDamage(Object* _pTarget, int _damage);

	// ** 데미지를 받음
	void TakeDamage(int _damage);

	// ** 스폰
	void Spawn(); 

	// ** 죽음
	void Die();

	// ** Move Info 초기화
	void InitMoveInfo();

	bool IsDied() { return isDied; }
	bool IsSpawning() { return isSpawing; }

	eEnemyType GetEnemyType() { return enemyType; }
	eItemType GetDropItemType() { return dropItemType; }
	int GetMaxHP() { return maxHP; }
	int GetHP() { return HP; }
	int GetHitPoint() { return hitScore; }
	int GetDeathPoint() { return deathScore; }
	int GetFireBulletIntervalTime() { return fireBulletIntervalTime; }
	Vector3 GetDestPosition() { return destPosition; }
	bool isMoving();

	void SetEnemyType(eEnemyType _enemyType);
	void SetDropItemType(eItemType _itemType) { dropItemType = _itemType; }
	void SetMaxHP(int _maxHP) { maxHP = _maxHP; }
	void SetHP(int _HP) { HP = _HP; }
	void SetHitPoint(int _point) { hitScore = _point; }
	void SetDeathPoint(int _point) { deathScore = _point; }
	void SetFireBulletIntervalTime(int _time) { fireBulletIntervalTime = _time; }
	void SetSpawnStatus(bool _isSpawing) { isSpawing = _isSpawing; }

	// ** 목적지로 이동
	void MoveTo(Vector3 _destPosition);

	// ** 현 위치에서 Spin. 
	void SpinLeft(bool _bLoop = false);
	void SpinRight(bool _bLoop = false);

	// ** 좌우로 왔다갔다 하며 진행. destPosition이 없을 시 무한 전진
	void BackAndForthLeft(Vector3 _destPosition = Vector3());
	void BackAndForthRight(Vector3 _destPosition = Vector3());

private:
	// ** Stage 전장을 벗어났는지 체크
	void CheckPositionInBkgBoundary();

public:
	Enemy();
	Enemy(const Transform& _rTransInfo) : Object(_rTransInfo) { }
	virtual ~Enemy();
};
