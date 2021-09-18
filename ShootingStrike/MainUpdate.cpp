#include "MainUpdate.h"
#include "Player.h"
#include "Enemy.h"
#include "SceneManager.h"
#include "InputManager.h"


MainUpdate::MainUpdate()
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
	InputManager::GetInstance()->CheckKeyInputStatus();

	SceneManager::GetInstance()->Update();
}

void MainUpdate::Render()
{
	SceneManager::GetInstance()->Render(m_hdc);
}

void MainUpdate::Release()
{
	SceneManager::GetInstance()->Release();
}
