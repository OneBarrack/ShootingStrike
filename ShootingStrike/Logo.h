#pragma once
#include "Scene.h"

class Object;
class Logo : public Scene
{
private:
	HWND hVideo;
	ULONGLONG tickTime;
	int videoPlayTime;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

private:
	// ** Logo Start
	void Start();

public:
	Logo();
	virtual ~Logo();
};