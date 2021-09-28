#include "MainUpdate.h"
#include "Player.h"
#include "Enemy.h"
#include "GameDataManager.h"
#include "SceneManager.h"
#include "InputManager.h"


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
}

void MainUpdate::Render()
{
	SceneManager::GetInstance()->Render(m_hdc);
}

void MainUpdate::Release()
{
	SceneManager::GetInstance()->Release();
}
