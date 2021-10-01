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
	Scene* pSceneState;

public:
	void SetScene(eSCENEID _sceneID);
	void Update();
	void Render(HDC _hdc);
	void Release();
private:
	SceneManager() : pSceneState(nullptr) {}
public:
	~SceneManager() { Release(); }
};

