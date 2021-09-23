#pragma once
#include "Object.h"

class Player : public Object
{
private:
	Bitmap* pPlayerImage;	

	int HP;
	int Damage;
	int Power;
	eBulletFireType FireType;

	bool bSpawing;
	bool bAttacking;
	bool bTakeDamage;
	bool bDied;

	int Frame;

	Vector3 OldPosition;
public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;	
	virtual void OnCollision(Object* _pObject)override;

	virtual Object* Clone()override { return new Player(*this); }

public:
	// ** Spawn / ReSpawn
	void SpawnPlayer() { bSpawing = true; };

	// ** 미사일 발사
	void Fire(eBulletFireType _FireType, int _Power, int _Damage);

	// ** 데미지를 입힘
	void ApplyDamage(Object* _pTarget, int _Damage);

	// ** 데미지를 받음
	void TakeDamage(int _Damage);

	// ** 죽음
	void Die() { bDied = true; };

private:
	// ** 플레이어가 화면 밖으로 나가지 않도록 처리 (우선 스테이지 배경 크기 수치 입력)
	void CheckPositionInsideScreen();

	// ** 플레이어의 캐릭터가 생성되는 애니메이션 동작. 
	// ** 발생조건 : 최초 스타트 / 죽은 후 다시 살아나는 상황
	bool RenderSpawn(HDC _hdc);

	// ** 플레이어의 이동방향에 따른 기체 애니메이션 동작. 
	void RenderPlayer(HDC _hdc);

public:
	Player();
	Player(const Transform& _rTransInfo) : Object(_rTransInfo) { }
	virtual ~Player();
};

