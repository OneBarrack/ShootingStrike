#pragma once
#include "Headers.h"

struct InputKeyInfo
{
	DWORD Key;
	InputKeyStatus KeyStatus;
};

class InputManager
{
private:
	static InputManager* Instance;
public:
	static InputManager* GetInstance()
	{
		if ( Instance == nullptr )
			Instance = new InputManager;

		return Instance;
	}
private:
	DWORD Key;
	DWORD OldKey;
	InputKeyInfo KeyInfo;
public:
	InputKeyInfo GetKeyInfo() const { return KeyInfo; }

	Vector3 GetMousePosition()
	{
		POINT ptMouse;

		// ** 마우스 좌표를 받아옴.
		GetCursorPos(&ptMouse);

		// ** 마우스 좌표를 현재 윈도우창의 좌표로 변경.
		ScreenToClient(g_hWnd, &ptMouse);

		return Vector3((float)ptMouse.x, (float)ptMouse.y);
	}

	void CheckKey();
private:
	void SetupKey();
	void SetupKeyInfo();
private:
	InputManager();
public:
	~InputManager() {}
};

