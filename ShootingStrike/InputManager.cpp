#include "InputManager.h"

InputManager* InputManager::Instance = nullptr;

InputManager::InputManager()
{
	AddKey(eInputKey::KEY_UP, VK_UP);
	AddKey(eInputKey::KEY_UP, 'W');
	AddKey(eInputKey::KEY_DOWN, VK_DOWN);		
	AddKey(eInputKey::KEY_DOWN, 'S');
	AddKey(eInputKey::KEY_LEFT, VK_LEFT);		
	AddKey(eInputKey::KEY_LEFT, 'A');
	AddKey(eInputKey::KEY_RIGHT, VK_RIGHT);	
	AddKey(eInputKey::KEY_RIGHT, 'D');
	AddKey(eInputKey::KEY_ESCAPE, VK_ESCAPE);
	AddKey(eInputKey::KEY_SPACE, VK_SPACE);
	AddKey(eInputKey::KEY_ENTER, VK_RETURN);
	AddKey(eInputKey::KEY_LBUTTON, VK_LBUTTON);
}

void InputManager::AddKey(eInputKey _Key, DWORD _dwKey)
{
	SameKeyList[_Key].push_back(_dwKey);
}

void InputManager::CheckKeyInputStatus()
{
	for ( auto KeyList : SameKeyList )
	{		
		eInputKey Key = KeyList.first;
		vector<DWORD> SameKeys = KeyList.second;

		SetKeyStatus(KeyInfo[Key], IsKeyPressed(SameKeys));
	}
}

bool InputManager::IsKeyPressed(vector<DWORD> _SameKeys)
{
	for ( DWORD Key : _SameKeys )
	{
		DWORD KeyState = GetAsyncKeyState(Key);

		if ( KeyState & 0x8000 )
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
