#include "MainUpdate.h"
#include "Player.h"
#include "Enemy.h"
#include "GameDebugManager.h"
#include "GameDataManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include "SoundManager.h"

MainUpdate::MainUpdate()
	: mHdc(NULL)
{

}

MainUpdate::~MainUpdate()
{
	Release();
}


void MainUpdate::Initialize()
{
	srand(GetTickCount64());

	mHdc = GetDC(g_hWnd);
		
	SceneManager::GetInstance()->SetScene(eSCENEID::LOGO);
}

void MainUpdate::Update()
{
	InputManager::GetInstance()->CheckKeyInput();	
	SoundManager::GetInstance()->Update();
	SceneManager::GetInstance()->Update();
	GameDataManager::GetInstance()->Update();	
	GameDebugManager::GetInstance()->Update();
}

void MainUpdate::Render()
{
	// ** Buffer DC
	HDC bufferDC = RenderManager::GetBufferDC();
	SceneManager::GetInstance()->Render(bufferDC);	
	GameDebugManager::GetInstance()->Render(bufferDC);

	// ** Logo Page를 제외하고 HDC 렌더링
	if ( SceneManager::GetInstance()->GetCurrentSceneID() != eSCENEID::LOGO)	
		RenderManager::RenderToScreen(mHdc);
}

void MainUpdate::Release()
{
	SceneManager::GetInstance()->Release();
	GameDebugManager::GetInstance()->Release();
	ObjectManager::GetInstance()->Release();
	SoundManager::GetInstance()->Release();
}
