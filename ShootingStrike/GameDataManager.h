#include "Headers.h"

class GameDataManager
{
private:
	static GameDataManager* pInstance;

public:
	static GameDataManager* GetInstance()
	{
		if ( pInstance == nullptr )
			pInstance = new GameDataManager;

		return pInstance;
	}

private:
	int playerLife;
	int score;
	int FPS;

public:
	void Initialize();
	void Update();

	int GetPlayerLife() { return playerLife; }
	int GetScore() { return score; }
	int GetFPS() { return FPS; }
	
	void AddScore(int _score);

private:
	// ** FPS ���
	void CalcFPS();

public:
	GameDataManager();
	~GameDataManager();
};