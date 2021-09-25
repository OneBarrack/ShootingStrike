#pragma once
#include "Scene.h"


class Object;
class Stage : public Scene
{
private:
	Object* pBackground;	
	Object* pPlayer;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

private:
	// ** 오브젝트가 Stage 내부를 벗어났는지 체크
	void CheckPositionInBkgBoundary(eObjectKey _ObjectKey);

public:
	Stage();
	virtual ~Stage();
};