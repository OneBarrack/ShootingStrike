#pragma once
#include "Headers.h"


class Bitmap
{
private:
	HDC hdc, MemDC;
	HBITMAP hBitmap, OldBitmap;
public:
	Bitmap* LoadBmp(const LPCWSTR _FileName);
	void Release();
public:
	HDC GetMemDC() const { return MemDC; };

public:
	Bitmap();
	~Bitmap();
};

