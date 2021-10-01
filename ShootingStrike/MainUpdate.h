#pragma once
#include "Headers.h"

class MainUpdate
{
private:
	HDC	mHdc;

public:
	void Initialize();
	void Update();
	void Render();
	void Release();

public:
	MainUpdate();
	~MainUpdate();
};



// ** UI
// ** »ç¿îµå
