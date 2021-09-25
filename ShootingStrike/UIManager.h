#pragma once
#include "Headers.h"

class Button;
class UIManager
{
public:
	static Button* MakeButton(Transform _TransInfo, Transform _Collider, eImageKey _ImageKey);
};

