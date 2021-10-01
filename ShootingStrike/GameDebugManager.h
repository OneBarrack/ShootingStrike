#include "Headers.h"

class GameDebugManager
{
	enum class eDebugMode
	{
		NONE,
		PRINT_TEXTINFO,
		DRAW_COLLISION,
		ALL
	};

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
	eDebugMode bDebugMode;

public:
	void Initialize();
	void Update();
	void Render(HDC _hdc);
	void Release();

private:
	void PrintTextForGameInfo(HDC _hdc);
	void DrawCollisionBoundary(HDC _hdc);

public:
	GameDebugManager();
	~GameDebugManager();
};