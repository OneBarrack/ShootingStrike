#include "RenderManager.h"

RenderManager* RenderManager::Instance = nullptr;

void RenderManager::Render(HDC _hdc)
{
	BitBlt(_hdc,
		0, 0,
		WindowsWidth,
		WindowsHeight,
		GetBufferDC(),
		0, 0,
		SRCCOPY);
}
