#pragma once
#include "Headers.h"

class Scene
{
public:
	bool isStartingScene;
	bool isEndingScene;

public:
	virtual void Initialize() PURE;
	virtual void Update() PURE;
	virtual void Render(HDC _hdc) PURE;
	virtual void Release() PURE;

public:
	Scene();
	virtual ~Scene();
};
