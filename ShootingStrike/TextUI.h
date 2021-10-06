#pragma once
#include "UIBridge.h"

class TextUI : public UIBridge
{
	enum class eTextType
	{
		ALPHABET,
		NUMBER	,
		SPECIAL	,
	};

public:
	typedef UIBridge Super;

private:
	// ** Text 출력에 사용할 이미지
	Bitmap* pTextImage;

	// ** 받아온 문자열을 문자 단위로 나누어 저장한 리스트
	vector<pair<eTextType, int>> splitTextList;

	// ** 텍스트의 크기
	int textSize;

	// ** 유효한 텍스트인지 ( 사용가능한 문자로만 이루어져 있는지 )
	bool isValidText;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

	virtual Bridge* Clone() override { return new TextUI(*this); }

public:
	bool SetText(string _text, int _textSize);

public:
	TextUI();
	virtual ~TextUI();
};

