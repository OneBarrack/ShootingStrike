#pragma once
#include "Headers.h"
#include "Object.h"

class SpawnPatternScript
{
public:
	virtual void Run() PURE;

public:
	SpawnPatternScript() {}
	~SpawnPatternScript() {}
};

