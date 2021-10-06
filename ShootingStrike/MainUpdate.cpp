#include "MainUpdate.h"
#include "Player.h"
#include "Enemy.h"
#include "GameDebugManager.h"
#include "GameDataManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "ObjectManager.h"


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
	mHdc = GetDC(g_hWnd);

	SceneManager::GetInstance()->SetScene(eSCENEID::LOGO);
}

void MainUpdate::Update()
{
	InputManager::GetInstance()->CheckKeyInput();	
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

	// ** HDC
	RenderManager::RenderToScreen(mHdc);
}

void MainUpdate::Release()
{
	SceneManager::GetInstance()->Release();
	GameDebugManager::GetInstance()->Release();
	ObjectManager::GetInstance()->Release();
}
