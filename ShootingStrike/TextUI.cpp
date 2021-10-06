#include "TextUI.h"
#include "BitmapManager.h"

TextUI::TextUI()
	: pTextImage(nullptr)
	, isValidText(true)
	, textSize(0)
{

}

TextUI::~TextUI()
{
}


void TextUI::Initialize()
{
	Super::Initialize();

	if ( !pTextImage )
		pTextImage = BitmapManager::GetInstance()->GetImage(eImageKey::TEXT);

	key = eBridgeKey::UI_TEXT;
	isValidText = true;
}

void TextUI::Update()
{
	Super::Update();
}

void TextUI::Render(HDC _hdc)
{
	Super::Render(_hdc);

	if ( pTextImage && isValidText )
	{
		for ( int textOrder = 0; textOrder < splitTextList.size(); ++textOrder )
		{			
			eTextType textType = splitTextList[textOrder].first;
			int segmentOffset = splitTextList[textOrder].second;

			// ** Score
			TransparentBlt(_hdc, // ** 최종 출력 위치
				int(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f) + (textSize * textOrder)),
				int(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
				int(textSize),
				int(textSize),
				pTextImage->GetMemDC(),
				int(pTextImage->GetSegmentationScale().x * segmentOffset),
				int(pTextImage->GetSegmentationScale().y * static_cast<int>(textType)),
				int(pTextImage->GetSegmentationScale().x),
				int(pTextImage->GetSegmentationScale().y),
				RGB(255, 0, 255));
		}
	}
}

void TextUI::Release()
{
	Super::Release();

	pTextImage = nullptr;
}

bool TextUI::SetText(string _text, int _textSize)
{
	textSize = _textSize;

	for ( char c : _text )
	{
		if ( isalpha(c) )
		{
			if ( isupper(c) )
			{
				splitTextList.push_back(make_pair(eTextType::ALPHABET, c - 'A'));
			}
			else // isLower(c)
			{
				splitTextList.push_back(make_pair(eTextType::ALPHABET, c - 'a'));
			}
		}
		else if ( isdigit(c) )
		{
			splitTextList.push_back(make_pair(eTextType::NUMBER, c));
		}
		else
		{
			switch ( c )
			{
				case ' ':  splitTextList.push_back(make_pair(eTextType::SPECIAL, 0)); break;
				case '!':  splitTextList.push_back(make_pair(eTextType::SPECIAL, 1)); break;
				case '?':  splitTextList.push_back(make_pair(eTextType::SPECIAL, 2)); break;
				case '=':  splitTextList.push_back(make_pair(eTextType::SPECIAL, 3)); break;
				case '-':  splitTextList.push_back(make_pair(eTextType::SPECIAL, 4)); break;
				case '.':  splitTextList.push_back(make_pair(eTextType::SPECIAL, 5)); break;
				case ':':  splitTextList.push_back(make_pair(eTextType::SPECIAL, 6)); break;
				case '\'': splitTextList.push_back(make_pair(eTextType::SPECIAL, 7)); break;
				case ',':  splitTextList.push_back(make_pair(eTextType::SPECIAL, 8)); break;
				case '/':  splitTextList.push_back(make_pair(eTextType::SPECIAL, 9)); break;
				default:
					splitTextList.clear();
					isValidText = false;
					return isValidText;
			}
		}
	}

	isValidText = true;
	return isValidText;
}