#include "BackAndForthEnemy.h"
#include "Object.h"
#include "BitmapManager.h"
#include "SpawnManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "SpawnManager.h"
#include "MathManager.h"
#include "GameDataManager.h"

BackAndForthEnemy::BackAndForthEnemy()
	: angle(0)
	, bFindPerpendicularDirection(false)
{
}

BackAndForthEnemy::~BackAndForthEnemy()
{

}


void BackAndForthEnemy::Initialize()
{
	Super::Initialize();

	key = eBridgeKey::ENEMY_BACK_AND_FORTH;

	time = GetTickCount64();
	angle = 0;
	perpendicularDirection = Vector3();
	bFindPerpendicularDirection = false;
}

void BackAndForthEnemy::Update()
{
	// ** Owner의 데이터를 받아옴
	ReceiveInfoFromOwner();

	Super::Update();

	// ** 따로 스폰 동작없음
	if ( isSpawing )
		isSpawing = false;

	// ** 수직방향 이동 속도
	int BackAndForthSpeed = 3;

	// ** 수직 벡터를 구한다
	if ( !bFindPerpendicularDirection )
	{
		bFindPerpendicularDirection = true;

		if ( startDirection == eBackAndForthDirection::LEFT )
		{
			perpendicularDirection.x = transInfo.Direction.y;
			perpendicularDirection.y = -transInfo.Direction.x;
		}
		else // startDirection == eBackAndForthDirection::RIGHT
		{
			perpendicularDirection.x = -transInfo.Direction.y;
			perpendicularDirection.y = transInfo.Direction.x;
		}			
	}

	// ** 360도 기준 Angle 초기화
	if ( angle > 360 )
	{
		angle = 0;
	}

	// ** 한쪽 수직방향으로 갔다가 돌아오도록
	transInfo.Position.x += perpendicularDirection.x * BackAndForthSpeed * sinf(MathManager::DegreeToRadian(angle));
	transInfo.Position.y += perpendicularDirection.y * BackAndForthSpeed * sinf(MathManager::DegreeToRadian(angle));
		
	angle += BackAndForthSpeed;
	
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


void BackAndForthEnemy::Render(HDC _hdc)
{
	Super::Render(_hdc);

	//if ( !pImage )
	//	return;

	RenderManager::DrawRect(_hdc, transInfo, RGB(120, 13, 150));
}

void BackAndForthEnemy::Release()
{
	Super::Release();
}