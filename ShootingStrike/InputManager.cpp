#include "InputManager.h"

InputManager* InputManager::Instance = nullptr;

InputManager::InputManager() :
	Key(0),
	OldKey(0)
{
	KeyInfo.Key = 0;
	KeyInfo.KeyStatus = InputKeyStatus::NONE;
}

void InputManager::CheckKey()
{
	SetupKey();
	SetupKeyInfo();
}

void InputManager::SetupKey()
{
	Key = 0;

	if ( GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W') )
		Key |= KEY_UP;

	if ( GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S') )
		Key |= KEY_DOWN;

	if ( GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A') )
		Key |= KEY_LEFT;

	if ( GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D') )
		Key |= KEY_RIGHT;

	if ( GetAsyncKeyState(VK_ESCAPE) )
		Key |= KEY_ESCAPE;

	if ( GetAsyncKeyState(VK_SPACE) )
		Key |= KEY_SPACE;

	if ( GetAsyncKeyState(VK_RETURN) )
		Key |= KEY_ENTER;

	if ( GetAsyncKeyState(VK_LBUTTON) )
		Key |= KEY_LBUTTON;
}

void InputManager::SetupKeyInfo()
{
	if ( Key == OldKey )
	{
		if ( Key == 0 )
		{
			KeyInfo.Key = 0;
			KeyInfo.KeyStatus = InputKeyStatus::NONE;
		}
		else
		{
			KeyInfo.KeyStatus = InputKeyStatus::PRESSED;
		}
	}
	else
	{
		if ( Key == 0 )
		{
			KeyInfo.Key = OldKey;
			KeyInfo.KeyStatus = InputKeyStatus::UP;
		}
		else
		{
			KeyInfo.Key = Key;
			KeyInfo.KeyStatus = InputKeyStatus::DOWN;
		}
	}

	OldKey = Key;
}
