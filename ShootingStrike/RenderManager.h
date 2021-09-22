#pragma once
#include "Headers.h"
#include "BitmapManager.h"

class RenderManager
{
private:
	static RenderManager* Instance;
public:
	static RenderManager* GetInstance()
	{
		if ( Instance == nullptr )
			Instance = new RenderManager;

		return Instance;
	}

public:
	HDC GetBufferDC() { return BitmapManager::GetInstance()->GetImage(eImageKey::BUFFER)->GetMemDC(); }
	void Render(HDC _hdc);
};

