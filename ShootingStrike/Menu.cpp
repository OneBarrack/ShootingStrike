#include "Menu.h"
#include "SceneManager.h"

Menu::Menu()
{

}

Menu::~Menu()
{

}

void Menu::Initialize()
{

}

void Menu::Update()
{
	if (GetAsyncKeyState('S'))
		SceneManager::GetInstance()->SetScene(eSCENEID::STAGE);
}

void Menu::Render(HDC _hdc)
{

}

void Menu::Release()
{

}
