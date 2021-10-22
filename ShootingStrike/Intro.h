#pragma once
#include "Scene.h"

class Object;
class Intro : public Scene
{
private:
	HWND hVideo;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

private:
	// ** Intro Start
	void Start();

public:
	Intro();
	virtual ~Intro();
};