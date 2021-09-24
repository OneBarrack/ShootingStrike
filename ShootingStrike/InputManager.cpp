#include "InputManager.h"

#define CheckKeyInputState(_Key, _State) (InputManager::GetInstance()->GetKeyState(_Key) == _State)

InputManager* InputManager::Instance = nullptr;

InputManager::InputManager()
{
	// ** Key_MAX 크기만큼 사이즈 할당
	OverlapKeyList.resize(static_cast<int>(eInputKey::KEY_MAX));
	KeyInfo.resize(static_cast<int>(eInputKey::KEY_MAX));
	
	AddOverlapKey(eInputKey::KEY_UP, VK_UP);
	AddOverlapKey(eInputKey::KEY_UP, 'W');
	AddOverlapKey(eInputKey::KEY_DOWN, VK_DOWN);
	AddOverlapKey(eInputKey::KEY_DOWN, 'S');
	AddOverlapKey(eInputKey::KEY_LEFT, VK_LEFT);
	AddOverlapKey(eInputKey::KEY_LEFT, 'A');
	AddOverlapKey(eInputKey::KEY_RIGHT, VK_RIGHT);	
	AddOverlapKey(eInputKey::KEY_RIGHT, 'D');
	AddOverlapKey(eInputKey::KEY_ESCAPE, VK_ESCAPE);
	AddOverlapKey(eInputKey::KEY_SPACE, VK_SPACE);
	AddOverlapKey(eInputKey::KEY_ENTER, VK_RETURN);
	AddOverlapKey(eInputKey::KEY_LBUTTON, VK_LBUTTON);
}

void InputManager::AddOverlapKey(eInputKey _Key, DWORD _dwKey)
{
	OverlapKeyList[static_cast<int>(_Key)].push_back(_dwKey);
}

void InputManager::InitKeyInfo()
{
	for ( int Key = 0; Key < static_cast<int>(eInputKey::KEY_MAX); ++Key )
	{
		SetKeyState(KeyInfo[Key], IsKeyPressed(OverlapKeyList[Key]));
	}
}

Vector3 InputManager::GetMousePosition()
{
	POINT ptMouse;

	// ** 마우스 좌표를 받아옴.
	GetCursorPos(&ptMouse);

	// ** 마우스 좌표를 현재 윈도우창의 좌표로 변경.
	ScreenToClient(g_hWnd, &ptMouse);

	return Vector3((float)ptMouse.x, (float)ptMouse.y);
}

bool InputManager::IsKeyPressed(vector<DWORD> _OverlapKeys)
{
	for ( DWORD Key : _OverlapKeys )
	{
		if ( GetAsyncKeyState(Key) & 0x8000 )
		{
			return true;
		}
	}

	return false;
}

void InputManager::SetKeyState(eKeyInputState& _KeyState, bool _IsKeyPressed)
{
	if ( _IsKeyPressed )
	{
		if ( _KeyState == eKeyInputState::DOWN ||
			_KeyState == eKeyInputState::PRESSED )
		{
			_KeyState = eKeyInputState::PRESSED;
		}
		else
		{
			_KeyState = eKeyInputState::DOWN;
		}
	}
	else
	{
		if ( _KeyState == eKeyInputState::DOWN ||
			_KeyState == eKeyInputState::PRESSED )
		{
			_KeyState = eKeyInputState::UP;
		}
		else
		{
			_KeyState = eKeyInputState::NONE;
		}
	}
}
