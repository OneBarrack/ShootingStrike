#include "NormalGoEnemy.h"
#include "Object.h"
#include "BitmapManager.h"
#include "SpawnManager.h"
#include "InputManager.h"
#include "RenderManager.h"

NormalGoEnemy::NormalGoEnemy()
{
}

NormalGoEnemy::~NormalGoEnemy()
{

}


void NormalGoEnemy::Initialize()
{
	Super::Initialize();

	key = eBridgeKey::ENEMY_NORMAL_GO;
}

void NormalGoEnemy::Update()
{
	Super::Update();

	// ** Owner의 데이터를 받아옴
	ReceiveInfoFromOwner();
		
	transInfo.Position.x += transInfo.Direction.x * speed;
	transInfo.Position.y += transInfo.Direction.y * speed;

	SendInfoToOwner();

	//bulletScript.Run();
}


void NormalGoEnemy::Render(HDC _hdc)
{
	Super::Render(_hdc);

	//if ( !pImage )
	//	return;

	RenderManager::DrawRect(_hdc, transInfo);
}

void NormalGoEnemy::Release()
{
	Super::Release();
}