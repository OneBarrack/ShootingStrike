#pragma once
#include "Headers.h"
#include "BitmapManager.h"

class RenderManager
{
private:
	enum class eFadeStatus
	{
		FADE_IN,
		FADE_OUT,
	};

public:
	static HDC GetBufferDC() { return BitmapManager::GetInstance()->GetImage(eImageKey::BUFFER)->GetMemDC(); }	
	static void RenderToScreen(HDC _hdc);
	static void DrawRect(HDC _hdc, Transform _transInfo, COLORREF _color = RGB(0,0,0), bool _bFillInside = false);
	static void DrawEllipse(HDC _hdc, Transform _transInfo, COLORREF _color = RGB(0, 0, 0), bool _bFillInside = false);
	static bool FadeIn(HDC _hdc) { return FadeAnimation(_hdc, eFadeStatus::FADE_IN); }
	static bool FadeOut(HDC _hdc) { return FadeAnimation(_hdc, eFadeStatus::FADE_OUT); }

private:
	static bool FadeAnimation(HDC _hdc, eFadeStatus fadeStatus);
};

