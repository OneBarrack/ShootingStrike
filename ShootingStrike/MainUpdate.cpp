#include "MainUpdate.h"
#include "Player.h"
#include "Enemy.h"
#include "GameDebugManager.h"
#include "GameDataManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "RenderManager.h"


MainUpdate::MainUpdate()
	: m_hdc(NULL)
{

}

MainUpdate::~MainUpdate()
{
	Release();
}


void MainUpdate::Initialize()
{
	m_hdc = GetDC(g_hWnd);

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
	HDC BufferDC = RenderManager::GetBufferDC();
	
	SceneManager::GetInstance()->Render(BufferDC);	
	GameDebugManager::GetInstance()->Render(BufferDC);

	RenderManager::RenderToScreen(m_hdc);
}

void MainUpdate::Release()
{
	SceneManager::GetInstance()->Release();

	GameDebugManager::GetInstance()->Release();
}
