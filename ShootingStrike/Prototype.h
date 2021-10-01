#pragma once
#include "Headers.h"

class Object;
class Bridge;
class Prototype
{
private:
	// ** Object Prototype
	map<eObjectKey, Object*> objectPrototypeList;

	// ** Bridge Prototype
	map<eBridgeKey, Bridge*> bridgePrototypeList;

public:
	void CreatePrototype();
	Object* FindPrototypeObject(eObjectKey _key);
	Bridge* FindPrototypeBridge(eBridgeKey _key);

public:
	Prototype();
	~Prototype();
};

