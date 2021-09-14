#pragma once
#include "Headers.h"

class Object;
class Prototype
{
private:
	map<eObjectKey, Object*> PrototypeList;
public:
	void CreatePrototype();
	Object* FindPrototypeObject(eObjectKey _Key);
public:
	Prototype();
	~Prototype();
};

