#include "Intro.h"

Intro::Intro()
{

}

Intro::~Intro()
{
	Release();
}

void Intro::Initialize()
{
	// ** Initialize
	
	hVideo = MCIWndCreate(g_hWnd, NULL,
		MCIWNDF_NOPLAYBAR | WS_VISIBLE | WS_CHILD, L"../Resource/Video/Intro.wmv");

	MoveWindow(hVideo, 0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT, NULL);
	MCIWndPlay(hVideo);

	/******* Logo Start *******/
	Start();
}

void Intro::Update()
{
}

void Intro::Render(HDC _hdc)
{	
}

void Intro::Release()
{
	
}

void Intro::Start()
{
	// ...
}