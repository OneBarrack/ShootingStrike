#pragma once
#include "Object.h"

class Background : public Object
{
private:
	// ** Image를 자를때 사용되는 Offset, 이미지 이동 속도와 동일
	int Offset;
	
	// ** Image를 끝까지 그려내어 이어 붙여야 할지 판단하는 변수
	bool bAttached;

public:
	virtual void Initialize()override;
	virtual int Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;
	virtual void OnCollision(Object* _pObject)override;

	virtual Object* Clone()
	{
		return new Background(*this);
	};
public:
	Background();
	virtual ~Background();
};