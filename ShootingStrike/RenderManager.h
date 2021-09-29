#pragma once
#include "Headers.h"
#include "BitmapManager.h"

class RenderManager
{
public:
	static HDC GetBufferDC() { return BitmapManager::GetInstance()->GetImage(eImageKey::BUFFER)->GetMemDC(); }	
	static void RenderToScreen(HDC _hdc);
	static void DrawRect(HDC _hdc, Transform _TransInfo, COLORREF _Color = RGB(0,0,0));
	static void DrawEllipse(HDC _hdc, Transform _TransInfo, COLORREF _Color = RGB(0, 0, 0));
};

