#pragma once
#include "Scene.h"

class Object;
class Menu : public Scene
{
private:
	Object* pBackground;
	Object* pPlayButton;
	Object* pQuitButton;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

public:
	Menu();
	virtual ~Menu();
};