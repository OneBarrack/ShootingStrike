#pragma once
#include "Headers.h"

class Scene;
class SceneManager
{
private:
	static SceneManager* pInstance;
public:
	static SceneManager* GetInstance()
	{
		if (pInstance == nullptr)
			pInstance = new SceneManager;

		return pInstance;
	}
private:
	// ** 현재 Scene 정보
	Scene* pSceneState;
	eSCENEID curSceneId;

	// ** 다음 Scene 정보
	eSCENEID nextSceneId;

public:
	eSCENEID GetCurrentSceneID();
	void SetScene(eSCENEID _sceneID);
	
	void Update();
	void Render(HDC _hdc);
	void Release();

private:
	void SceneStart(eSCENEID _sceneID);

private:
	SceneManager() : pSceneState(nullptr) {}
public:
	~SceneManager() { Release(); }
};

