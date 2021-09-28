#pragma once
#include "Headers.h"
#include "Object.h"

class Bridge
{
protected:
	Object* pOwner;
	eBridgeKey Key;

public:
	virtual void Initialize()PURE;
	virtual void Update()PURE;
	virtual void Render(HDC _hdc)PURE;
	virtual void Release()PURE;

	virtual Bridge* Clone()PURE;

	virtual void ReceiveInfoFromOwner()PURE;
	virtual void SendInfoToOwner()PURE;

public:
	void SetOwner(Object* _pObject) { pOwner = _pObject; }
	Object* GetOwner() { return pOwner; }

	eBridgeKey GetKey() { return Key; }

public:
	Bridge();
	virtual ~Bridge();
};

