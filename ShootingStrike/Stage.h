#pragma once
#include "Scene.h"


class Object;
class Stage : public Scene
{
private:
	Object* State_Back;
	Object* m_pPlayer;
	Object* m_pEffect;
	vector<Object*>* EnemyList;
	vector<Object*>* BulletList;

	// ** 타일 생성 개수
	int TileWidthCnt;
	int TileHeightCnt;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

private:
	// ** 모든 활성화 오브젝트 간 충돌 검사
	void CheckCollisionForAllObjects();

	// ** 모든 오버젝트의 Status를 체크하여 Update 또는 Recall 처리
	void UpdateForAllObjects();

	void RenderForAllObjects(HDC _hdc);

public:
	Stage();
	virtual ~Stage();
};