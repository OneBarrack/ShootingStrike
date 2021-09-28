#include "Headers.h"

class GameDataManager
{
private:
	static GameDataManager* Instance;

public:
	static GameDataManager* GetInstance()
	{
		if ( Instance == nullptr )
			Instance = new GameDataManager;

		return Instance;
	}

private:
	int Score;
	int Frame;
	int FPS;
	ULONGLONG Time;

public:
	void Initialize();
	void Update();

	int GetScore() { return Score; }
	int GetFPS() { return FPS; }
	
	void AddScore(int _Score);

private:
	void CalcFPS();

public:
	GameDataManager();
	~GameDataManager();
};