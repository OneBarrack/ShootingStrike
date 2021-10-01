#pragma once
#include "Object.h"

class ButtonUI : public Object
{
	enum class eButtonState
	{
		NORMAL	,
		HOVER	,
		PRESSED	,
	};

private:
	eButtonState buttonState;

	bool bExistHoverImage;
	bool bExistPressedImage;
	bool bOnClick;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;
	virtual void OnCollision(Object* _pObject) override;

	virtual Object* Clone() { return new ButtonUI(*this); }

public:
	// ** 클릭 되었는지
	bool OnClick() { return bOnClick; }

public:
	ButtonUI();
	ButtonUI(const Transform& _rTransInfo) : Object(_rTransInfo) {}
	virtual ~ButtonUI();
};

