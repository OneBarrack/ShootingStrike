#include "RenderManager.h"

void RenderManager::DrawRect(HDC _hdc, Transform _TransInfo, COLORREF _Color)
{
	HPEN	hPen	= CreatePen(PS_SOLID, 2, _Color);
	HGDIOBJ hOldPen = SelectObject(_hdc, hPen);

	//HBRUSH hBrush = CreateSolidBrush(_Color); // ** 색상 넣기
	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);	// ** 투명
	HGDIOBJ hOldBrush = SelectObject(_hdc, hBrush);
	
	Rectangle(_hdc,
		int(_TransInfo.Position.x - (_TransInfo.Scale.x / 2)),
		int(_TransInfo.Position.y - (_TransInfo.Scale.y / 2)),
		int(_TransInfo.Position.x + (_TransInfo.Scale.x / 2)),
		int(_TransInfo.Position.y + (_TransInfo.Scale.y / 2)));

	SelectObject(_hdc, hOldPen);
	SelectObject(_hdc, hOldBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
}

void RenderManager::DrawEllipse(HDC _hdc, Transform _TransInfo, COLORREF _Color)
{
	HPEN	hPen = CreatePen(PS_SOLID, 2, _Color);
	HGDIOBJ hOldPen = SelectObject(_hdc, hPen);

	//HBRUSH hBrush = CreateSolidBrush(_Color); // ** 색상 넣기
	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);	// ** 투명
	HGDIOBJ hOldBrush = SelectObject(_hdc, hBrush);

	Ellipse(_hdc,
		int(_TransInfo.Position.x - (_TransInfo.Scale.x / 2)),
		int(_TransInfo.Position.y - (_TransInfo.Scale.y / 2)),
		int(_TransInfo.Position.x + (_TransInfo.Scale.x / 2)),
		int(_TransInfo.Position.y + (_TransInfo.Scale.y / 2)));

	SelectObject(_hdc, hOldPen);
	SelectObject(_hdc, hOldBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
}

void RenderManager::RenderToScreen(HDC _hdc)
{
	BitBlt(_hdc,
		0, 0,
		WindowsWidth,
		WindowsHeight,
		GetBufferDC(),
		0, 0,
		SRCCOPY);
}
