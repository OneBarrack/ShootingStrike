#pragma once
#include "Scene.h"


class Object;
class Stage : public Scene
{
private:
	Object* pPlayer;
	Object* pBackground;
	Object* pLeftSideBackground;
	Object* pRightSideBackground;
	Object* pScoreTextUI;
	Object* pScoreUI;
	Object* pLifeTextUI;
	Object* pLifeUI;
	Object* pBossAngelEnemy;
	Object* pBossEnemyProgressBar;
	Object* pMapProgress;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

private:
	// ** Stage Start
	void Start();

public:
	Stage();
	virtual ~Stage();
};