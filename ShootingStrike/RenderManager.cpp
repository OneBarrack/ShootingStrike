#include "RenderManager.h"

void RenderManager::DrawRect(HDC _hdc, Transform _transInfo, COLORREF _color)
{
	HPEN hPen = CreatePen(PS_SOLID, 2, _color);
	HGDIOBJ hOldPen = SelectObject(_hdc, hPen);

	//HBRUSH hBrush = CreateSolidBrush(_Color); // ** 색상 넣기
	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);	// ** 투명
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

void RenderManager::DrawEllipse(HDC _hdc, Transform _transInfo, COLORREF _color)
{
	HPEN hPen = CreatePen(PS_SOLID, 2, _color);
	HGDIOBJ hOldPen = SelectObject(_hdc, hPen);

	//HBRUSH hBrush = CreateSolidBrush(_Color); // ** 색상 넣기
	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);	// ** 투명
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
