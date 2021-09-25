#pragma once
#include "Scene.h"

class Object;
class Logo : public Scene
{
private:
	Object* pBackground;
	Object* pLogoTitle;
	Object* pPlayButton;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;
public:
	Logo();
	virtual ~Logo();
};