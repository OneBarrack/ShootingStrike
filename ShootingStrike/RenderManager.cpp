#include "RenderManager.h"

void RenderManager::DrawRect(HDC _hdc, Transform _transInfo, COLORREF _color, bool _bFillInside)
{
	HPEN hPen = CreatePen(PS_SOLID, 2, _color);
	HGDIOBJ hOldPen = SelectObject(_hdc, hPen);

	HBRUSH hBrush;	
	if ( _bFillInside )
		hBrush = CreateSolidBrush(_color); // ** 색상 넣기
	else
		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH); // ** 투명

	HGDIOBJ hOldBrush = SelectObject(_hdc, hBrush);
	
	Rectangle(_hdc,
		int(_transInfo.Position.x - (_transInfo.Scale.x / 2)),
		int(_transInfo.Position.y - (_transInfo.Scale.y / 2)),
		int(_transInfo.Position.x + (_transInfo.Scale.x / 2)),
		int(_transInfo.Position.y + (_transInfo.Scale.y / 2)));

	SelectObject(_hdc, hOldPen);
	SelectObject(_hdc, hOldBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
}

void RenderManager::DrawEllipse(HDC _hdc, Transform _transInfo, COLORREF _color, bool _bFillInside)
{
	HPEN hPen = CreatePen(PS_SOLID, 2, _color);
	HGDIOBJ hOldPen = SelectObject(_hdc, hPen);

	HBRUSH hBrush;
	if ( _bFillInside )
		hBrush = CreateSolidBrush(_color); // ** 색상 넣기
	else
		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH); // ** 투명

	HGDIOBJ hOldBrush = SelectObject(_hdc, hBrush);

	Ellipse(_hdc,
		int(_transInfo.Position.x - (_transInfo.Scale.x / 2)),
		int(_transInfo.Position.y - (_transInfo.Scale.y / 2)),
		int(_transInfo.Position.x + (_transInfo.Scale.x / 2)),
		int(_transInfo.Position.y + (_transInfo.Scale.y / 2)));

	SelectObject(_hdc, hOldPen);
	SelectObject(_hdc, hOldBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
}

bool RenderManager::FadeAnimation(HDC _hdc, eFadeStatus fadeStatus)
{
	static BYTE alpha = 0;
	int fadeSpeed = 3;

	if ( fadeStatus == eFadeStatus::FADE_IN  && alpha > 0   ) alpha -= fadeSpeed;
	if ( fadeStatus == eFadeStatus::FADE_OUT && alpha < 255 ) alpha += fadeSpeed;

	BLENDFUNCTION bf;
	bf.AlphaFormat			= 0;			// ** 일반 비트맵 0, 32비트 비트맵 AC_SRC_ALPHA
	bf.BlendFlags			= 0;			// ** 사용되지 않는 옵션. 무조건 0
	bf.BlendOp				= AC_SRC_OVER;  // ** AC_SRC_OVER
	bf.SourceConstantAlpha	= alpha;		// ** 투명도(투명 0 - 불투명 255)

	// ** Fade Background 이미지를 바탕으로 Fade 효과 부여
	AlphaBlend(_hdc, 0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT,
		BitmapManager::GetInstance()->GetImage(eImageKey::FADEBACK_BLACK)->GetMemDC(),
		0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT, bf);

	// ** alpha가 0 또는 255라면 Fade Animation이 끝난것.
	return (alpha == 0 || alpha == 255);
}

void RenderManager::RenderToScreen(HDC _hdc)
{
	BitBlt(_hdc,
		0, 0,
		WINDOWS_WIDTH,
		WINDOWS_HEIGHT,
		GetBufferDC(),
		0, 0,
		SRCCOPY);
}
