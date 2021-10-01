#pragma once
#include "Object.h"

class ScoreUI : public Object
{
private:
	Bitmap* pScoreImage;
	Bitmap* pNumberImage;
	queue<int> numberList;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;
	virtual void OnCollision(Object* _pObject) override;

	virtual Object* Clone() { return new ScoreUI(*this); };

private:
	// ** Score를 뒷자리 수 부터 차례대로 numberList에 넣음
	void MakeScoreNumberList();

public:
	ScoreUI();
	ScoreUI(const Transform& _rTransInfo) : Object(_rTransInfo) {}
	virtual ~ScoreUI();
};

