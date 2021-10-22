#pragma once
#include "UIBridge.h"

class GameOverUI : public UIBridge
{
public:
	typedef UIBridge Super;

private:
	Bitmap* pGameOverImage;
	Bitmap* pFadeBackImage;
	Object* pYesButton;
	Object* pNoButton;

	// ** AlphaBlend시 사용할 데이터
	BYTE alpha;
	int fadeSpeed;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

	virtual Bridge* Clone() override { return new GameOverUI(*this); }

private:
	void InitButton();

public:
	GameOverUI();
	virtual ~GameOverUI();
};

