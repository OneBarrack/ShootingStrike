#pragma once
#include "UIBridge.h"

class ButtonUI : public UIBridge
{
public:
	typedef UIBridge Super;

private:
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

	virtual Bridge* Clone() override { return new ButtonUI(*this); }

public:
	// ** 클릭 되었는지
	bool OnClick() { return bOnClick; }

public:
	ButtonUI();
	virtual ~ButtonUI();
};

