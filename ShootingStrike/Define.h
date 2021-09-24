#pragma once

#define GAME_DEBUG_MODE 1

#define PI 3.141592f

#define CheckKeyInputState(_Key, _State) (InputManager::GetInstance()->GetKeyState(_Key) == _State)
