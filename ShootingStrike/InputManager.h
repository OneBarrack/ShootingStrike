#pragma once
#include "Headers.h"

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
	// ** 같은 기능을 하는 Key들을 모아놓은 List
	vector<vector<DWORD>> OverlapKeyList;

	// ** Key에 대한 입력 정보가 담겨있음
	vector<eKeyInputStatus> KeyInfo;

public:
	// ** InputKey에 대한 입력 정보 체크
	void CheckKeyInputStatus();

	// ** 해당 Key에 대한 입력 정보 반환
	eKeyInputStatus GetKeyStatus(eInputKey _Key) { return KeyInfo[static_cast<int>(_Key)]; }

	Vector3 GetMousePosition()
	{
		POINT ptMouse;

		// ** 마우스 좌표를 받아옴.
		GetCursorPos(&ptMouse);

		// ** 마우스 좌표를 현재 윈도우창의 좌표로 변경.
		ScreenToClient(g_hWnd, &ptMouse);

		return Vector3((float)ptMouse.x, (float)ptMouse.y);
	}

private:
	// ** 같은 기능을 하는 Key 중 하나라도 눌렀는지 확인하는 함수
	bool IsKeyPressed(vector<DWORD> _OverlapKeys);

	// ** Key에 대한 현재 입력상태 세팅
	void SetKeyStatus(eKeyInputStatus& _KeyStatus, bool _IsKeyPressed);

	void AddOverlapKey(eInputKey _Key, DWORD _dwKey);
private:
	InputManager();
public:
	~InputManager() {}
};

