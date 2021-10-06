#pragma once
#include "UIBridge.h"

class ScoreUI : public UIBridge
{
public:
	typedef UIBridge Super;

private:
	Bitmap* pNumberImage;
	queue<int> numberList;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

	virtual Bridge* Clone() override { return new ScoreUI(*this); }

private:
	// ** Score를 뒷자리 수 부터 차례대로 numberList에 넣음
	void MakeScoreNumberList();

public:
	ScoreUI();
	virtual ~ScoreUI();
};

