#include "GoAndSpinEnemy.h"
#include "Object.h"
#include "BitmapManager.h"
#include "SpawnManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "SpawnManager.h"
#include "MathManager.h"
#include "GameDataManager.h"

GoAndSpinEnemy::GoAndSpinEnemy()
{
}

GoAndSpinEnemy::~GoAndSpinEnemy()
{

}


void GoAndSpinEnemy::Initialize()
{
	Super::Initialize();

	key = eBridgeKey::ENEMY_BACK_AND_FORTH;

	time = GetTickCount64();
	spinDirection = eSpinDirection::LEFT;
}

void GoAndSpinEnemy::Update()
{
	// ** Owner의 데이터를 받아옴
	ReceiveInfoFromOwner();

	Super::Update();

	// ** 따로 스폰 동작없음
	if ( isSpawing )
		isSpawing = false;

	// ** 목적지에 도달했을 경우 Spin 동작
	if ( bArrivedToDest )
	{
		float angle;
		if ( spinDirection == eSpinDirection::LEFT )    
			angle = -1.0f;
		else // spinDirection == eSpinDirection::RIGHT
			angle = 1.0f;
 
		transInfo.Direction = MathManager::RotateByDegree(transInfo.Direction, angle);
	}
	
	// ** 도착 전 이라면 그대로 전진	
	transInfo.Position.x += transInfo.Direction.x * speed;
	transInfo.Position.y += transInfo.Direction.y * speed;
	
	collider = transInfo;

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


void GoAndSpinEnemy::Render(HDC _hdc)
{
	Super::Render(_hdc);

	//if ( !pImage )
	//	return;

	RenderManager::DrawRect(_hdc, transInfo, RGB(120, 13, 150));
}

void GoAndSpinEnemy::Release()
{
	Super::Release();
}