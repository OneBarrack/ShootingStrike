#pragma once
#include "Headers.h"

class Object;
class Bridge;
class Prototype
{
private:
	// ** Object Prototype
	map<eObjectKey, Object*> ObjectPrototypeList;

	// ** Bridge Prototype
	map<eBridgeKey, Bridge*> BridgePrototypeList;

public:
	void CreatePrototype();
	Object* FindPrototypeObject(eObjectKey _Key);
	Bridge* FindPrototypeBridge(eBridgeKey _Key);

public:
	Prototype();
	~Prototype();
};

