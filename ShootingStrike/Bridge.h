#pragma once
#include "Headers.h"

class Object;
class Bridge
{
protected:
	string DrawKey;
	Object* RootObject;
public:
	virtual void Initialize()PURE;
	virtual void Update(Transform& _rTransInfo)PURE;
	virtual void Render(HDC _hdc)PURE;
	virtual void Release()PURE;
public:
	void SetObject(Object* _pObject) { RootObject = _pObject; }
public:
	Bridge();
	virtual ~Bridge();
};

