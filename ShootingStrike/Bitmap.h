#pragma once
#include "Headers.h"


class Bitmap
{
private:
	HDC hdc;
	HDC memDC;
	HBITMAP hBitmap;
	HBITMAP oldBitmap;

	eImageKey imageKey;
	Vector3 imageScale;
	Vector3 segmentationScale;

public:
	void Initialize();

	HDC GetMemDC() const { return memDC; };

	Vector3 GetScale() { return imageScale; }
	Vector3 GetSegmentationScale() { return segmentationScale; }

	void SetScale(Vector3 _scale) { imageScale = _scale; }
	void SetSegmentationScale(Vector3 _scale) { segmentationScale = _scale; }

	void Release();

private:
	void LoadBmp(const LPCWSTR _fileName);
	
public:
	Bitmap(eImageKey _imageKey, const LPCWSTR _fileName);
	~Bitmap();
};

