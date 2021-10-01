#include "Headers.h"

class GameDebugManager
{
private:
	enum class eDebugMode
	{
		NONE,
		PRINT_TEXTINFO,
		DRAW_COLLISION,
		ALL
	};

private:
	static GameDebugManager* pInstance;
public:
	static GameDebugManager* GetInstance()
	{
		if ( pInstance == nullptr )
			pInstance = new GameDebugManager;

		return pInstance;
	}

private:
	eDebugMode bDebugMode;

public:
	void Initialize();
	void Update();
	void Render(HDC _hdc);
	void Release();

private:
	// ** Game Info에 대한 Text 출력
	void PrintTextForGameInfo(HDC _hdc);

	// ** Collision Box 바운더리 렌더링
	void DrawCollisionBoundary(HDC _hdc);

public:
	GameDebugManager();
	~GameDebugManager();
};