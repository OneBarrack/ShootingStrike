#pragma once
#include "Headers.h"
#include "Object.h"

class Bridge
{
protected:
	string DrawKey;
	Object* pOwner;

public:
	virtual void Initialize()PURE;
	virtual void Update()PURE;
	virtual void Render(HDC _hdc)PURE;
	virtual void Release()PURE;

public:
	void SetOwner(Object* _pObject) { pOwner = _pObject; }
	Object* GetOwner() { return pOwner; }

public:
	Bridge();
	virtual ~Bridge();
};

