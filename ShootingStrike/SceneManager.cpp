#include "SceneManager.h"
#include "Logo.h"
#include "Menu.h"
#include "Stage.h"

SceneManager* SceneManager::pInstance = nullptr;


eSCENEID SceneManager::GetCurrentSceneID()
{
	return curSceneId;
}

void SceneManager::SceneStart(eSCENEID _sceneID)
{
	::Safe_Delete(pSceneState);	

	curSceneId = nextSceneId;
	switch ( curSceneId )
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

void SceneManager::SetScene(eSCENEID _sceneID)
{
	nextSceneId = _sceneID;
}

void SceneManager::Update()
{
	// ** 다음 SceneId가 NONE이 아니면, Scene 변경이 일어난 것이므로 
	// ** 현재 Scene을 nextSceneId의 Scene으로 초기화 및 nextSceneId를 NONE으로 초기화
	if ( nextSceneId != eSCENEID::NONE )
	{
		SceneStart(nextSceneId);
		nextSceneId = eSCENEID::NONE;
	}

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