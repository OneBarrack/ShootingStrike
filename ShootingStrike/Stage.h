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

	Object* pEnemyBoss;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

private:
	// ** 오브젝트들이 메인 Background를 벗어났는지 체크
	void CheckPositionInBkgBoundary(eObjectKey _ObjectKey);

public:
	Stage();
	virtual ~Stage();
};