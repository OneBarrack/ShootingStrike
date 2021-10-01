#pragma once
#include "Headers.h"

class InputManager
{
private:
	static InputManager* pInstance;
public:
	static InputManager* GetInstance()
	{
		if ( pInstance == nullptr )
			pInstance = new InputManager;

		return pInstance;
	}
private:
	// ** 같은 기능을 하는 Key들을 모아놓은 List
	vector<vector<DWORD>> overlapKeyList;

	// ** Key에 대한 입력 정보가 담겨있음
	vector<eKeyInputState> keyInfo;

public:
	// ** InputKey에 대한 입력 정보 체크
	void CheckKeyInput();

	// ** 마우스 Position 반환
	Vector3 GetMousePosition();
	
	// ** 해당 Key에 대한 입력 정보 반환
	inline eKeyInputState GetKeyState(eInputKey _Key) { return keyInfo[static_cast<int>(_Key)]; }

private:
	// ** 같은 기능을 하는 Key 중 하나라도 눌렀는지 확인하는 함수
	bool IsKeyPressed(vector<DWORD> _overlapKeys);

	// ** Key에 대한 현재 입력상태 세팅
	void SetKeyState(eKeyInputState& _keyState, bool _IsKeyPressed);

	void AddOverlapKey(eInputKey _key, DWORD _dwKey);

private:
	InputManager();
public:
	~InputManager() {}
};

