#pragma once
#include "Object.h"

class ScoreUI : public Object
{
private:
	Bitmap* pScoreImage;
	Bitmap* pNumberImage;
	queue<int> NumberList;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;
	virtual void OnCollision(Object* _pObject)override;

	virtual Object* Clone() { return new ScoreUI(*this); };

private:
	void MakeScoreNumberList();

public:
	ScoreUI();
	ScoreUI(const Transform& _rTransInfo) : Object(_rTransInfo) {}
	virtual ~ScoreUI();
};

