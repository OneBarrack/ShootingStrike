#pragma once
#include "Scene.h"

class Object;
class Button;
class Logo : public Scene
{
private:
	Object* pBackground;
	Button* pPlayButton;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;
public:
	Logo();
	virtual ~Logo();
};