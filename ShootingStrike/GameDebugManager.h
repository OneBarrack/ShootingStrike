#include "Headers.h"

class GameDebugManager
{
private:
	static GameDebugManager* Instance;

public:
	static GameDebugManager* GetInstance()
	{
		if ( Instance == nullptr )
			Instance = new GameDebugManager;

		return Instance;
	}

private:
	bool bDebugMode;

public:
	void Initialize();
	void Update();
	void Render(HDC _hdc);
	void Release();

public:
	GameDebugManager();
	~GameDebugManager();
};