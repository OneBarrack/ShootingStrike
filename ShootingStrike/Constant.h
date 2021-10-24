#pragma once

// ** Windows Boundary
const int WINDOWS_WIDTH = 1280;
const int WINDOWS_HEIGHT = 720;

// ** Key Input
const DWORD KEY_UP		= 0x00000001;
const DWORD KEY_DOWN	= 0x00000002;
const DWORD KEY_LEFT	= 0x00000004;
const DWORD KEY_RIGHT	= 0x00000008;
const DWORD KEY_ESCAPE	= 0x00000010;
const DWORD KEY_SPACE	= 0x00000020;
const DWORD KEY_ENTER	= 0x00000040;
const DWORD KEY_Z		= 0x00000080;
const DWORD KEY_X		= 0x00000100;
const DWORD KEY_PLUS	= 0x00000200;
const DWORD KEY_MINUS	= 0x00000400;

// ** 마우스 좌측 키 입력 확인.
const DWORD KEY_LBUTTON = 0x00000200;
const DWORD KEY_F8		= 0x00000400;

// ** Sound
const float SOUND_VOLUME = 0.05f;
const float SOUND_VOLUME_MAX = 1.0f;
const float SOUND_VOLUME_MIN = 0.0f;
