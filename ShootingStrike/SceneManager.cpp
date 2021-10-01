#include "SceneManager.h"
#include "Logo.h"
#include "Menu.h"
#include "Stage.h"

SceneManager* SceneManager::pInstance = nullptr;


void SceneManager::SetScene(eSCENEID _sceneID)
{
	::Safe_Delete(pSceneState);
	
	switch (_sceneID)
	{
	case eSCENEID::LOGO:
		pSceneState = new Logo;
		break;

	case eSCENEID::MENU:
		pSceneState = new Menu;
		break;

	case eSCENEID::STAGE:
		pSceneState = new Stage;
		break;

	case eSCENEID::EXIT:
		exit(NULL);
		break;
	}

	pSceneState->Initialize();
}

void SceneManager::Update()
{
	pSceneState->Update();
	
}

void SceneManager::Render(HDC _hdc)
{
	pSceneState->Render(_hdc);
}

void SceneManager::Release()
{
	::Safe_Delete(pSceneState);
}