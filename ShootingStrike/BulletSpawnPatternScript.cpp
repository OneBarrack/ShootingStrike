#include "BulletSpawnPatternScript.h"
#include "Object.h"
#include "ObjectManager.h"
#include "SpawnManager.h"
#include "MathManager.h"
#include "GoTargetAfterDelayBullet.h"
#include "SpreadAfterDelayBullet.h"

BulletSpawnPatternScript::BulletSpawnPatternScript()
	: pOwner(nullptr)
	, spawnPattern(eBulletSpawnPattern::NONE)
	, spawnTransInfo(Transform())
	, damage(0)	
	, bReady(false)
{
}

BulletSpawnPatternScript::~BulletSpawnPatternScript()
{
}

void BulletSpawnPatternScript::Initialize()
{
	pOwner = nullptr;
	spawnPattern = eBulletSpawnPattern::NONE;
	damage = 0;
	spawnTransInfo = Transform();
	bReady = false;
}

void BulletSpawnPatternScript::ReadyToSpawn(Object* _pOwner, eBulletSpawnPattern _spawnPattern, Transform _spawnTransInfo, int _damage)
{
	pOwner = _pOwner;
	spawnPattern = _spawnPattern;
	spawnTransInfo = _spawnTransInfo;
	damage = _damage;

	bReady = true;
}

void BulletSpawnPatternScript::Run()
{
	// ** Owner가 없거나 Pattern 설정이 되어있지 않다면 리턴
	if ( !pOwner || spawnPattern == eBulletSpawnPattern::NONE )	
		return;

	Spawn();
	Update();
}

void BulletSpawnPatternScript::Spawn()
{
	static eBulletSpawnPattern prevSpawnPattern = spawnPattern;
	static ULONGLONG spawnTime = 0;
	static int cycleCount = 0;

	// ** 새로운 패턴으로 첫 진입 시
	if ( bReady )
	{
		// ** spawnTime 및 cycleCount 초기화
		spawnTime = 0;
		cycleCount = 0;
		bReady = false;
	}

	switch ( spawnPattern )
	{
		case eBulletSpawnPattern::SPIN_GO:
		{
			//** Spin 패턴 : 360도 회전하며 순차적으로 Bullet 생성

			int maxCycleCount = 200; // ** 최대 발동 횟수
			int spawnCycleTime = 10; // ** 발동 시간 간격
			float angleGap = 13.0f;	 // ** AngleGap : 총알간 간격(각도)

			if ( spawnTime + spawnCycleTime < GetTickCount64() )
			{
				spawnTime = GetTickCount64();				

				// ** 상방 기준 현재 각도
				float angle = angleGap * cycleCount;

				// ** Bullet의 TransInfo 설정
				Transform bulletTransInfo;								
				bulletTransInfo.Direction = MathManager::RotateByDegree(spawnTransInfo.Direction, angle);
				bulletTransInfo.Position.x = spawnTransInfo.Position.x + bulletTransInfo.Direction.x * spawnTransInfo.Scale.x * 0.5f;
				bulletTransInfo.Position.y = spawnTransInfo.Position.y + bulletTransInfo.Direction.y * spawnTransInfo.Scale.x * 0.5f;
				bulletTransInfo.Scale = Vector3(10.0f, 10.0f);

				// ** Bullet의 Speed 설정
				float bulletSpeed = 3.0f;

				// ** Bullet Spawn
				SpawnManager::SpawnBullet(pOwner, bulletTransInfo, bulletSpeed, damage, eBridgeKey::BULLET_NORMAL);

				++cycleCount;
			}

			// ** 패턴 종료 시 초기화
			if ( maxCycleCount == cycleCount )
			{
				Initialize();
			}
			break;
		}
		case eBulletSpawnPattern::MULTI_SPIN_GO:
		{
			//** Multi Spin 패턴 : 360도 기준 일정 간격으로 시작지점들을 나누고 모든 시작지점에 Spin 패턴을 적용

			int maxCycleCount = 100; // ** 최대 발동 횟수
			int spawnCycleTime = 50; // ** 발동 시간 간격
			int angleGap = 30;	 // ** AngleGap : 총알간 간격(각도)

			if ( spawnTime + spawnCycleTime < GetTickCount64() )
			{
				spawnTime = GetTickCount64();

				int bulletCount = 360 / angleGap;
				for ( int i = 0; i < bulletCount; ++i )
				{
					// ** 우측 기준 현재 각도
					int angle = angleGap * i + (cycleCount * 7);

					// ** Bullet의 TransInfo 설정
					Transform bulletTransInfo;
					bulletTransInfo.Direction = MathManager::RotateByDegree(spawnTransInfo.Direction, angle);
					bulletTransInfo.Position.x = spawnTransInfo.Position.x + bulletTransInfo.Direction.x * spawnTransInfo.Scale.x * 0.5f;
					bulletTransInfo.Position.y = spawnTransInfo.Position.y + bulletTransInfo.Direction.y * spawnTransInfo.Scale.x * 0.5f;
					bulletTransInfo.Scale = Vector3(10.0f, 10.0f);

					// ** Bullet의 Speed 설정
					float bulletSpeed = 3.0f;

					// ** Bullet Spawn
					SpawnManager::SpawnBullet(pOwner, bulletTransInfo, bulletSpeed, damage, eBridgeKey::BULLET_NORMAL);
				}

				++cycleCount;
			}

			// ** 패턴 종료 시 초기화
			if ( maxCycleCount == cycleCount )
			{
				Initialize();
			}
			break;
		}
		case eBulletSpawnPattern::N_POLYGON_GO:
		{
			//** N각형의 도형으로 총알 발사

			int maxCycleCount = 1;	  // ** 최대 발동 횟수
			int spawnCycleTime = 500; // ** 발동 시간 간격			
			float bulletSpeed = 3.0f; // ** Bullet Speed

			// ** N각형의 꼭짓점 개수
			int vertex = 3;

			// ** 발사될 총알개수. N의 배수만큼만 발동됨
			int bulletCount = vertex * 10;

			// ** 두 꼭짓점 사이 총알들로 인해 생길 동일한 길이의 간격 개수
			int equalPartsCount = static_cast<int>(bulletCount / vertex);
			
			// ** Vertex간 간격 각도
			int angleGapForVertex = static_cast<int>(360 / vertex);			
			
			// ** 꼭짓점을 담을 임시 벡터
			vector<Transform> vertexList;

			if ( spawnTime + spawnCycleTime < GetTickCount64() )
			{
				spawnTime = GetTickCount64();

				// ** 꼭짓점
				for ( int i = 0; i < vertex; ++i )
				{
					// ** 꼭짓점 각도
					int angle = angleGapForVertex * i;

					// ** 꼭짓점의 TransInfo 설정
					Transform bulletTransInfo;
					bulletTransInfo.Direction = MathManager::RotateByDegree(spawnTransInfo.Direction, angle);
					bulletTransInfo.Position.x = spawnTransInfo.Position.x + bulletTransInfo.Direction.x * spawnTransInfo.Scale.x * 0.5f;
					bulletTransInfo.Position.y = spawnTransInfo.Position.y + bulletTransInfo.Direction.y * spawnTransInfo.Scale.x * 0.5f;
					bulletTransInfo.Scale = Vector3(10.0f, 10.0f);
					
					// ** Bullet Spawn
					SpawnManager::SpawnBullet(pOwner, bulletTransInfo, bulletSpeed, damage, eBridgeKey::BULLET_NORMAL);

					vertexList.push_back(bulletTransInfo);
				}

				// 중심에서 Vertex까지의 거리
				int distToVertex = static_cast<int>(MathManager::GetDistance(spawnTransInfo.Position, vertexList[0].Position));

				for ( int i = 1; i < equalPartsCount; ++i )
				{
					for ( size_t j = 0; j < vertexList.size(); ++j )
					{		
						// ** 꼭짓점 사이 나뉘어진 간격만큼 이동시켜 위치를 잡기 위해 현재 꼭짓점과 다음 꼭짓점 인덱스를 설정
						int curIndex = j;
						int nextIndex = (curIndex < (int)vertexList.size() - 1) ? curIndex + 1 : 0;

						// ** 꼭짓점 사이 Bullet의 TransInfo 설정						
						Transform bulletTransInfo;
						bulletTransInfo.Position = vertexList[curIndex].Position + (((vertexList[nextIndex].Position - vertexList[curIndex].Position) / (float)equalPartsCount) * (float)i);
						bulletTransInfo.Direction = MathManager::GetDirection(spawnTransInfo.Position, bulletTransInfo.Position);
						bulletTransInfo.Scale = Vector3(10.0f, 10.0f);

						// ** Bullet의 Speed에 곱해줄 ratio를 구함 
						// ** 중심에서 Vertex까지의 거리에 대한 중심에서 현재 bullet위치의 비율을 곱해준다
						float curDist = MathManager::GetDistance(spawnTransInfo.Position, bulletTransInfo.Position);
						float distRatio = curDist / distToVertex;

						// ** Bullet Spawn
						SpawnManager::SpawnBullet(pOwner, bulletTransInfo, bulletSpeed * distRatio, damage, eBridgeKey::BULLET_NORMAL);
					}
				}

				++cycleCount;
			}

			// ** 패턴 종료 시 초기화
			if ( maxCycleCount == cycleCount )
			{
				Initialize();
			}
			break;
		}
		case eBulletSpawnPattern::CIRCLE_GO:
		{
			//** 원 형태로 발사

			int maxCycleCount = 5;		// ** 최대 발동 횟수
			int spawnCycleTime = 500;	// ** 발동 시간 간격
			float angleGap = 13.0f;		// ** AngleGap : 총알간 간격(각도)

			if ( spawnTime + spawnCycleTime < GetTickCount64() )
			{
				spawnTime = GetTickCount64();

				int bulletCount = static_cast<int>(360 / angleGap) + 1;
				for ( int i = 0; i < bulletCount; ++i )
				{
					// ** 우측 기준 현재 각도
					float angle = angleGap * i;

					// ** Bullet의 TransInfo 설정
					Transform bulletTransInfo;
					bulletTransInfo.Direction = MathManager::RotateByDegree(spawnTransInfo.Direction, angle);
					bulletTransInfo.Position.x = spawnTransInfo.Position.x + bulletTransInfo.Direction.x * spawnTransInfo.Scale.x * 0.5f;
					bulletTransInfo.Position.y = spawnTransInfo.Position.y + bulletTransInfo.Direction.y * spawnTransInfo.Scale.x * 0.5f;
					bulletTransInfo.Scale = Vector3(10.0f, 10.0f);

					// ** Bullet의 Speed 설정
					float bulletSpeed = 3.0f;

					// ** Bullet Spawn
					SpawnManager::SpawnBullet(pOwner, bulletTransInfo, bulletSpeed, damage, eBridgeKey::BULLET_NORMAL);
				}

				++cycleCount;
			}

			// ** 패턴 종료 시 초기화
			if ( maxCycleCount == cycleCount )
			{
				Initialize();
			}
			break;
		}
		case eBulletSpawnPattern::CIRCLE_GO_DELAY_GO_TARGET:
		{
			//** 원 형태로 발사 후 Delay시간이 지나면 타겟방향으로 방향을 틈

			int maxCycleCount = 5;		// ** 최대 발동 횟수
			int spawnCycleTime = 500;	// ** 발동 시간 간격
			float angleGap = 13.0f;		// ** AngleGap : 총알간 간격(각도)

			if ( spawnTime + spawnCycleTime < GetTickCount64() )
			{
				spawnTime = GetTickCount64();

				int bulletCount = static_cast<int>(360 / angleGap) + 1;
				for ( int i = 0; i < bulletCount; ++i )
				{
					// ** 현재 각도
					float angle = angleGap * i;

					// ** Bullet의 TransInfo 설정
					Transform bulletTransInfo;
					bulletTransInfo.Direction = MathManager::RotateByDegree(spawnTransInfo.Direction, angle);
					bulletTransInfo.Position.x = spawnTransInfo.Position.x + bulletTransInfo.Direction.x * spawnTransInfo.Scale.x * 0.5f;
					bulletTransInfo.Position.y = spawnTransInfo.Position.y + bulletTransInfo.Direction.y * spawnTransInfo.Scale.x * 0.5f;
					bulletTransInfo.Scale = Vector3(10.0f, 10.0f);

					// ** Bullet의 Speed 설정
					float bulletSpeed = 3.0f;

					Bridge* pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::BULLET_GO_TARGET_AFTER_DELAY);
					static_cast<GoTargetAfterDelayBullet*>(pBridge)->SetDelay(1000);

					// ** Bullet Spawn
					SpawnManager::SpawnBullet(pOwner, bulletTransInfo, bulletSpeed, damage, pBridge);
				}

				++cycleCount;
			}

			// ** 패턴 종료 시 초기화
			if ( maxCycleCount == cycleCount )
			{
				Initialize();
			}
			break;
		}
		case eBulletSpawnPattern::CIRCLE_STOP_DELAY_GO_TARGET:
		{
			//** 원 형태로 발사 후 Delay시간이 지나면 타겟방향으로 방향을 틈

			int maxCycleCount = 30;		// ** 최대 발동 횟수
			int spawnCycleTime = 200;	// ** 발동 시간 간격
			float angleGap = 60;		// ** AngleGap : 총알간 간격(각도)

			if ( spawnTime + spawnCycleTime < GetTickCount64() )
			{
				spawnTime = GetTickCount64();

				// ** 현재 각도
				float angle = angleGap * cycleCount;

				// ** Bullet의 TransInfo 설정
				Transform bulletTransInfo;
				bulletTransInfo.Direction = MathManager::RotateByDegree(spawnTransInfo.Direction, angle);
				bulletTransInfo.Position.x = spawnTransInfo.Position.x + bulletTransInfo.Direction.x * spawnTransInfo.Scale.x;
				bulletTransInfo.Position.y = spawnTransInfo.Position.y + bulletTransInfo.Direction.y * spawnTransInfo.Scale.x;
				bulletTransInfo.Scale = Vector3(10.0f, 10.0f);
				bulletTransInfo.Direction = Vector3(0.0f, 0.0f);

				// ** Bullet의 Speed 설정
				float bulletSpeed = 3.0f;

				Bridge* pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::BULLET_GO_TARGET_AFTER_DELAY);
				static_cast<GoTargetAfterDelayBullet*>(pBridge)->SetDelay(1000);

				// ** Bullet Spawn
				SpawnManager::SpawnBullet(pOwner, bulletTransInfo, bulletSpeed, damage, pBridge);

				++cycleCount;
			}

			// ** 패턴 종료 시 초기화
			if ( maxCycleCount == cycleCount )
			{
				Initialize();
			}
			break;
		}
		case eBulletSpawnPattern::CIRCLE_GO_DELAY_SPREAD:
		{
			//** 원 형태로 발사 후 Delay시간이 지나면 타겟방향으로 방향을 틈

			int maxCycleCount = 5;		// ** 최대 발동 횟수
			int spawnCycleTime = 2000;	// ** 발동 시간 간격
			int angleGap = 60;			// ** AngleGap : 총알간 간격(각도)

			if ( spawnTime + spawnCycleTime < GetTickCount64() )
			{
				spawnTime = GetTickCount64();

				// ** Bullet의 TransInfo 설정
				Transform bulletTransInfo;
				bulletTransInfo.Position = Vector3(WINDOWS_WIDTH * 0.5f, 0.0f);
				bulletTransInfo.Scale = Vector3(10.0f, 10.0f);
				bulletTransInfo.Direction = Vector3(0.0f, 1.0f);

				// ** Bullet의 Speed 설정
				float bulletSpeed = 3.0f;

				int bulletCount = 4 + cycleCount;
				Bridge* pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::BULLET_SPREAD_AFTER_DELAY);
				static_cast<SpreadAfterDelayBullet*>(pBridge)->SetDelay(1000);
				static_cast<SpreadAfterDelayBullet*>(pBridge)->SetSpreadCount(3);
				static_cast<SpreadAfterDelayBullet*>(pBridge)->SetBulletCount(bulletCount);
				static_cast<SpreadAfterDelayBullet*>(pBridge)->SetIntervalAngle(360 / bulletCount);

				// ** Bullet Spawn
				SpawnManager::SpawnBullet(pOwner, bulletTransInfo, bulletSpeed, damage, pBridge);

				++cycleCount;
			}

			// ** 패턴 종료 시 초기화
			if ( maxCycleCount == cycleCount )
			{
				Initialize();
			}
			break;
		}
	}

	//** 현재 패턴은 이전 패턴이 됨
	prevSpawnPattern = spawnPattern;
}

void BulletSpawnPatternScript::Update()
{
}