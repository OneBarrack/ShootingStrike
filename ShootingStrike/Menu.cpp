#include "Menu.h"
#include "SceneManager.h"
#include "ObjectManager.h"

Menu::Menu()
{

}

Menu::~Menu()
{
	Release();
}

void Menu::Initialize()
{
	// ...

	/******* Menu Start *******/
	Start();
}

void Menu::Update()
{
	ObjectManager::GetInstance()->Update();

	if (GetAsyncKeyState('S'))
		SceneManager::GetInstance()->SetScene(eSCENEID::STAGE);
}

void Menu::Render(HDC _hdc)
{
	ObjectManager::GetInstance()->Render(_hdc);
}

void Menu::Release()
{

}

void Menu::Start()
{
}