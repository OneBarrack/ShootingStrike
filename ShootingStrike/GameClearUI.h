#pragma once
#include "UIBridge.h"

class GameClearUI : public UIBridge
{
public:
	typedef UIBridge Super;

private:
	Bitmap* pGameClearImage;
	Bitmap* pFadeBackImage;
	Object* pPlayTimeNameTextUI;
	Object* pPlayTimeTextUI;
	Object* pScoreNameTextUI;
	Object* pScoreUI;
	Object* pPressEnterTextUI;

	// ** Object들이 초기화 되었는지
	bool bInitializedObjects;

	// ** AlphaBlend시 사용할 데이터
	BYTE alpha;
	int fadeSpeed;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

	virtual Bridge* Clone() override { return new GameClearUI(*this); }

private:
	void InitTextObjects();

	string ConvertTimeToStrTimeFormat(ULONGLONG _time);	

public:
	GameClearUI();
	virtual ~GameClearUI();
};

