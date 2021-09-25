#pragma once
#include "Object.h"

class Background : public Object
{
//	enum class Image
//
//private:
//	Bitmap* pImage;
//	Vector3 Scale;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;
	virtual void OnCollision(Object* _pObject)override;

	virtual Object* Clone() { return new Background(*this); };
public:
	Background();
	virtual ~Background();
};