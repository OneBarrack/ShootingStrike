#pragma once
#include "Headers.h"


class Bitmap
{
private:
	HDC hdc;
	HDC MemDC;
	HBITMAP hBitmap;
	HBITMAP OldBitmap;

	Vector3 ImageScale;
	Vector3 SegmentationOffset;
	Vector3 SegmentationScale;

public:
	void Initialize(eImageKey _ImageKey, const LPCWSTR _FileName);

	HDC GetMemDC() const { return MemDC; };

	Vector3 GetScale() { return ImageScale; }
	Vector3 GetSegmentationOffset() { return SegmentationOffset; }
	Vector3 GetSegmentationScale() { return SegmentationScale; }

	void SetScale(Vector3 _Scale) { ImageScale = _Scale; }
	void SetSegmentationOffset(Vector3 _Offset) { SegmentationScale = _Offset; }
	void SetSegmentationScale(Vector3 _Scale) { SegmentationScale = _Scale; }

	void Release();

private:
	void LoadBmp(const LPCWSTR _FileName);
	
public:
	Bitmap(eImageKey _ImageKey, const LPCWSTR _FileName);
	~Bitmap();
};

