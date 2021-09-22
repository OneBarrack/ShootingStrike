#pragma once
#include "Headers.h"

class BitmapManager
{
private:
	static BitmapManager* Instance;
public:
	static BitmapManager* GetInstance()
	{
		if ( Instance == nullptr )
			Instance = new BitmapManager;

		return Instance;
	}

public:
	void Initialize();
	Bitmap* GetImage(const eImageKey _Key);

private:
	// imageKey enum값을 Key로 가지는 Bitmap List
	map<eImageKey, Bitmap*> ImageList;

public:
	const map<eImageKey, Bitmap*> GetImageList() { return ImageList; }
};