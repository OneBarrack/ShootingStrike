#include "InputManager.h"

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

void InputManager::CheckKeyInputStatus()
{
	for ( int Key = 0; Key < static_cast<int>(eInputKey::KEY_MAX); ++Key )
	{
		SetKeyStatus(KeyInfo[Key], IsKeyPressed(OverlapKeyList[Key]));
	}
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

void InputManager::SetKeyStatus(eKeyInputStatus& _KeyStatus, bool _IsKeyPressed)
{
	if ( _IsKeyPressed )
	{
		if ( _KeyStatus == eKeyInputStatus::DOWN ||
			_KeyStatus == eKeyInputStatus::PRESSED )
		{
			_KeyStatus = eKeyInputStatus::PRESSED;
		}
		else
		{
			_KeyStatus = eKeyInputStatus::DOWN;
		}
	}
	else
	{
		if ( _KeyStatus == eKeyInputStatus::DOWN ||
			_KeyStatus == eKeyInputStatus::PRESSED )
		{
			_KeyStatus = eKeyInputStatus::UP;
		}
		else
		{
			_KeyStatus = eKeyInputStatus::NONE;
		}
	}
}
