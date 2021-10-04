#include "BulletSpawnPatternScript.h"
#include "SpawnManager.h"
#include "Object.h"

BulletSpawnPatternScript::BulletSpawnPatternScript()
	: pOwner(nullptr)
	, spawnPattern(eBulletSpawnPattern::NONE)
	, damage(0)	
	, bReady(false)
{
}

BulletSpawnPatternScript::~BulletSpawnPatternScript()
{
}

void BulletSpawnPatternScript::Initialize(Object* _pOwner)
{
	if ( _pOwner ) 
		pOwner = _pOwner;

	spawnPattern = eBulletSpawnPattern::NONE;
	damage = 0;

	bReady = false;
}

void BulletSpawnPatternScript::ReadyToSpawn(eBulletSpawnPattern _SpawnPattern, int _damage)
{
	spawnPattern = _SpawnPattern;
	damage = _damage;

	bReady = true;
}

void BulletSpawnPatternScript::Run()
{
	if ( !pOwner || spawnPattern == eBulletSpawnPattern::NONE ) 
		return;

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
		case eBulletSpawnPattern::SPIN:
		{
			//** Spin 패턴 : 360도 회전하며 순차적으로 Bullet 생성

			int maxCycleCount = 500;		// ** 최대 발동 횟수
			int spawnCycleTime = 10;		// ** 발동 시간 간격
			int angleGap = 30;				// ** AngleGap : 총알간 간격(각도)

			if ( spawnTime + spawnCycleTime < GetTickCount64() )
			{
				spawnTime = GetTickCount64();

				int bulletCount = 360 / angleGap;

				// ** 상방 기준 현재 각도
				int angle = angleGap + (cycleCount * 13);

				// ** Bullet의 TransInfo 설정
				Transform bulletTransInfo;
				bulletTransInfo.Position = pOwner->GetPosition();
				bulletTransInfo.Scale = Vector3(10.0f, 10.0f);
				bulletTransInfo.Direction = Vector3(cosf(angle * PI / 180), -sinf(angle * PI / 180));

				// ** Bullet의 Speed 설정
				float bulletSpeed = 3.0f;

				// ** Bullet Spawn
				SpawnManager::SpawnBullet(pOwner, bulletTransInfo, bulletSpeed, damage, eBulletType::NORMAL);

				++cycleCount;
			}

			// ** 패턴 종료 시 초기화
			if ( maxCycleCount < cycleCount )
			{
				Initialize();
			}
			break;
		}			
		case eBulletSpawnPattern::MULTI_SPIN:
		{
			//** Multi Spin 패턴 : 360도 기준 일정 간격으로 시작지점들을 나누고 모든 시작지점에 Spin 패턴을 적용

			int maxCycleCount = 50;		// ** 최대 발동 횟수
			int spawnCycleTime = 50;		// ** 발동 시간 간격
			int angleGap = 30;				// ** AngleGap : 총알간 간격(각도)

			if ( spawnTime + spawnCycleTime < GetTickCount64() )
			{
				spawnTime = GetTickCount64();

				int bulletCount = 360 / angleGap;
				for ( int i = 0; i < bulletCount; ++i )
				{
					// ** 상방 기준 현재 각도
					int angle = angleGap * i + (cycleCount * 7);

					// ** Bullet의 TransInfo 설정
					Transform bulletTransInfo;
					bulletTransInfo.Position = pOwner->GetPosition();
					bulletTransInfo.Scale = Vector3(10.0f, 10.0f);
					bulletTransInfo.Direction = Vector3(cosf(angle * PI / 180), -sinf(angle * PI / 180));

					// ** Bullet의 Speed 설정
					float bulletSpeed = 3.0f;

					// ** Bullet Spawn
					SpawnManager::SpawnBullet(pOwner, bulletTransInfo, bulletSpeed, damage, eBulletType::NORMAL);
				}

				++cycleCount;
			}

			// ** 패턴 종료 시 초기화
			if ( maxCycleCount < cycleCount )
			{
				Initialize();
			}
			break;
		}
		case eBulletSpawnPattern::CIRCLE:
		{
			//** 원 형태로 발사

			int maxCycleCount = 5;		// ** 최대 발동 횟수
			int spawnCycleTime = 500;		// ** 발동 시간 간격
			int angleGap = 13;				// ** AngleGap : 총알간 간격(각도)

			if ( spawnTime + spawnCycleTime < GetTickCount64() )
			{
				spawnTime = GetTickCount64();

				int bulletCount = 360 / angleGap;
				for ( int i = 0; i < bulletCount; ++i )
				{
					// ** 상방 기준 현재 각도
					int angle = angleGap * i;

					// ** Bullet의 TransInfo 설정
					Transform bulletTransInfo;
					bulletTransInfo.Position = pOwner->GetPosition();
					bulletTransInfo.Scale = Vector3(10.0f, 10.0f);
					bulletTransInfo.Direction = Vector3(cosf(angle * PI / 180), -sinf(angle * PI / 180));

					// ** Bullet의 Speed 설정
					float bulletSpeed = 3.0f;

					// ** Bullet Spawn
					SpawnManager::SpawnBullet(pOwner, bulletTransInfo, bulletSpeed, damage, eBulletType::NORMAL);
				}

				++cycleCount;
			}

			// ** 패턴 종료 시 초기화
			if ( maxCycleCount < cycleCount )
			{
				Initialize();
			}
			break;
		}
	}

	//** 현재 패턴은 이전 패턴이 됨
	prevSpawnPattern = spawnPattern;
}
