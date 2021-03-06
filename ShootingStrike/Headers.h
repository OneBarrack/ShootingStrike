#pragma once

#include <Windows.h>
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <cassert>

using namespace std;

// ** Image
#pragma comment(lib, "msimg32.lib")

// ** Video
#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")

// ** Sound
#pragma comment(lib, "fmod_vc.lib")
#include <fmod.hpp>

#include "Struct.h"
#include "Enum.h"
#include "Constant.h"
#include "Define.h"
#include "Bitmap.h"

extern HWND g_hWnd;

template <typename T>
inline void Safe_Delete(T& _pObj)
{
	if (_pObj)
	{
		delete _pObj;
		_pObj = nullptr;
	}
}