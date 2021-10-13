#include "NormalEnemy.h"
#include "Object.h"
#include "BitmapManager.h"
#include "SpawnManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "SpawnManager.h"
#include "MathManager.h"
#include "GameDataManager.h"

NormalEnemy::NormalEnemy()
{
}

NormalEnemy::~NormalEnemy()
{

}


void NormalEnemy::Initialize()
{
	Super::Initialize();

	key = eBridgeKey::ENEMY_NORMAL;

	time = GetTickCount64();
}

void NormalEnemy::Update()
{
	// ** Owner의 데이터를 받아옴
	ReceiveInfoFromOwner();

	Super::Update();

	// ** 따로 스폰 동작없음
	if ( isSpawing )
		isSpawing = false;

	// ** 목적지에서 멈추어야 하고, 목적지에 도달했다면
	if ( bStopAtDest && bArrivedToDest )
	{
		// ** 정지상태 동작
	}
	// ** 위 조건이 아니라면 계속해서 이동한다
	else
	{
		transInfo.Position.x += transInfo.Direction.x * speed;
		transInfo.Position.y += transInfo.Direction.y * speed;

		collider = transInfo;
	}

	// ** 주기적 Bullet 발사
	if ( fireBulletIntervalTime > 0 && time + fireBulletIntervalTime < GetTickCount64() )
	{
		time = GetTickCount64();

		// ** 꼭짓점 사이 Bullet의 TransInfo 설정						
		Transform bulletTransInfo;
		bulletTransInfo.Position = transInfo.Position;
		bulletTransInfo.Direction = MathManager::GetDirection(transInfo.Position, GameDataManager::GetInstance()->GetPlayerPos());
		bulletTransInfo.Scale = Vector3(10.0f, 10.0f);

		// ** Bullet Spawn
		SpawnManager::SpawnBullet(pOwner, bulletTransInfo, 3.0f, 1, eBridgeKey::BULLET_NORMAL);
	}

	SendInfoToOwner();

	//bulletScript.Run();
}


void NormalEnemy::Render(HDC _hdc)
{
	Super::Render(_hdc);

	//if ( !pImage )
	//	return;

	RenderManager::DrawRect(_hdc, transInfo);
}

void NormalEnemy::Release()
{
	Super::Release();
}