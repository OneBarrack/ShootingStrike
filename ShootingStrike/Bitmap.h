#pragma once
#include "Headers.h"


class Bitmap
{
private:
	HDC hdc;
	HDC MemDC;
	HBITMAP hBitmap;
	HBITMAP OldBitmap;

	eImageKey ImageKey;
	Vector3 ImageScale;
	Vector3 SegmentationScale;

public:
	void Initialize();

	HDC GetMemDC() const { return MemDC; };

	Vector3 GetScale() { return ImageScale; }
	Vector3 GetSegmentationScale() { return SegmentationScale; }

	void SetScale(Vector3 _Scale) { ImageScale = _Scale; }
	void SetSegmentationScale(Vector3 _Scale) { SegmentationScale = _Scale; }

	void Release();

private:
	void LoadBmp(const LPCWSTR _FileName);
	
public:
	Bitmap(eImageKey _ImageKey, const LPCWSTR _FileName);
	~Bitmap();
};

