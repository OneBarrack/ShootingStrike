#include "EnemySpawnPatternScript.h"
#include "Object.h"
#include "ObjectManager.h"
#include "SpawnManager.h"
#include "MathManager.h"
#include "NormalEnemy.h"
#include "Enemy.h"
#include "Background.h"

EnemySpawnPatternScript::EnemySpawnPatternScript()
{
}

EnemySpawnPatternScript::~EnemySpawnPatternScript()
{
}

void EnemySpawnPatternScript::Initialize()
{
	readyPatternList = list<pair<Object*, eEnemySpawnPattern>>();
}

void EnemySpawnPatternScript::ReadyToSpawn(Object* _pOwner, eEnemySpawnPattern _spawnPattern)
{
	readyPatternList.push_back(make_pair(_pOwner, _spawnPattern));
}

void EnemySpawnPatternScript::Run()
{
	Spawn();
	Update();
}

void EnemySpawnPatternScript::Spawn()
{
	if ( readyPatternList.empty() )
		return;

	for ( auto listIter = readyPatternList.begin(); listIter != readyPatternList.end(); )
	{
		Bridge* pBridge = nullptr;
		Object* pObject = nullptr;

		Object* pOwner = listIter->first;
		eEnemySpawnPattern spawnPattern = listIter->second;

		bool bFinishedPattern = false;

		switch ( spawnPattern )
		{
			case eEnemySpawnPattern::DOWN_BACK_AND_FORTH_RED_ELF_2:
			{
				pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_NORMAL);
				pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
				pObject->SetTagName(eTagName::ENEMY_RED_ELF);
				pObject->SetPosition(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.3f), 
									 pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f));
				pObject->SetScale(60.0f, 40.0f);
				pObject->SetDirection(0.0f, 1.0f);
				pObject->SetSpeed(0.75f);
				pObject->SetBridge(pBridge);
				static_cast<Enemy*>(pObject)->SetEnemyType(eEnemyType::ENEMY_RED_ELF);
				static_cast<Enemy*>(pObject)->SetFireBulletIntervalTime(3000);
				static_cast<Enemy*>(pObject)->BackAndForthLeft();

				pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_NORMAL);
				pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
				pObject->SetTagName(eTagName::ENEMY_RED_ELF);
				pObject->SetPosition(pOwner->GetPosition().x + (pOwner->GetScale().x * 0.3f),
									 pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f));
				pObject->SetScale(60.0f, 40.0f);
				pObject->SetDirection(0.0f, 1.0f);
				pObject->SetSpeed(0.75f);
				pObject->SetBridge(pBridge);
				static_cast<Enemy*>(pObject)->SetEnemyType(eEnemyType::ENEMY_RED_ELF);
				static_cast<Enemy*>(pObject)->SetFireBulletIntervalTime(3000);
				static_cast<Enemy*>(pObject)->BackAndForthRight();

				bFinishedPattern = true;
				break;
			}
			case eEnemySpawnPattern::DOWN_BACK_AND_FORTH_RED_ELF_4:
			{
				pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_NORMAL);
				pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
				pObject->SetTagName(eTagName::ENEMY_RED_ELF);
				pObject->SetPosition(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.2f),
									 pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f));
				pObject->SetScale(60.0f, 40.0f);
				pObject->SetDirection(0.0f, 1.0f);
				pObject->SetSpeed(0.75f);
				pObject->SetBridge(pBridge);
				static_cast<Enemy*>(pObject)->SetEnemyType(eEnemyType::ENEMY_RED_ELF);
				static_cast<Enemy*>(pObject)->SetFireBulletIntervalTime(3000);
				static_cast<Enemy*>(pObject)->BackAndForthLeft();

				pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_NORMAL);
				pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
				pObject->SetTagName(eTagName::ENEMY_RED_ELF);
				pObject->SetPosition(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.4f),
									 pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f));
				pObject->SetScale(60.0f, 40.0f);
				pObject->SetDirection(0.0f, 1.0f);
				pObject->SetSpeed(0.75f);
				pObject->SetBridge(pBridge);
				static_cast<Enemy*>(pObject)->SetEnemyType(eEnemyType::ENEMY_RED_ELF);
				static_cast<Enemy*>(pObject)->SetFireBulletIntervalTime(3000);
				static_cast<Enemy*>(pObject)->BackAndForthLeft();

				pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_NORMAL);
				pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
				pObject->SetTagName(eTagName::ENEMY_RED_ELF);
				pObject->SetPosition(pOwner->GetPosition().x + (pOwner->GetScale().x * 0.2f),
									 pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f));
				pObject->SetScale(60.0f, 40.0f);
				pObject->SetDirection(0.0f, 1.0f);
				pObject->SetSpeed(0.75f);
				pObject->SetBridge(pBridge);
				static_cast<Enemy*>(pObject)->SetEnemyType(eEnemyType::ENEMY_RED_ELF);
				static_cast<Enemy*>(pObject)->SetFireBulletIntervalTime(3000);
				static_cast<Enemy*>(pObject)->BackAndForthRight();

				pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_NORMAL);
				pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
				pObject->SetTagName(eTagName::ENEMY_RED_ELF);
				pObject->SetPosition(pOwner->GetPosition().x + (pOwner->GetScale().x * 0.4f),
									 pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f));
				pObject->SetScale(60.0f, 40.0f);
				pObject->SetDirection(0.0f, 1.0f);
				pObject->SetSpeed(0.75f);
				pObject->SetBridge(pBridge);
				static_cast<Enemy*>(pObject)->SetEnemyType(eEnemyType::ENEMY_RED_ELF);
				static_cast<Enemy*>(pObject)->SetFireBulletIntervalTime(3000);
				static_cast<Enemy*>(pObject)->BackAndForthRight();
							
				bFinishedPattern = true;
				break;
			}
			case eEnemySpawnPattern::LEFT_TOP_TO_RIGHT_BOTTOM_SPIN:
			{
				static ULONGLONG spawnDelayTime = 0;
				static int spawnCount = 0;
				int delay = 500;
				int maxSpawnCount = 5;

				Vector3 leftTopPos = Vector3(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f),
											  pOwner->GetPosition().y - (pOwner->GetScale().y * 0.3f));				
				Vector3 rightBottomPos	= Vector3(pOwner->GetPosition().x + (pOwner->GetScale().x * 0.5f),
											  pOwner->GetPosition().y + (pOwner->GetScale().y * 0.3f));
				Vector3 centerPos = Vector3(leftTopPos.x + ((rightBottomPos.x - leftTopPos.x) * 0.5f),
											leftTopPos.y + ((rightBottomPos.y - leftTopPos.y) * 0.5f));

				// ** Spawn Count가 남았고 delay 시간이 지날때마다 스폰
				if ( spawnCount < maxSpawnCount && spawnDelayTime + delay < GetTickCount64() )
				{
					pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_NORMAL);
					pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
					pObject->SetTagName(eTagName::ENEMY_BLUE_ELF);
					pObject->SetPosition(leftTopPos);
					pObject->SetScale(40.0f, 40.0f);
					pObject->SetDirection(0.0f, 1.0f);
					pObject->SetSpeed(2.5f);
					pObject->SetBridge(pBridge);
					static_cast<Enemy*>(pObject)->SetEnemyType(eEnemyType::ENEMY_BLUE_ELF);
					static_cast<Enemy*>(pObject)->SetFireBulletIntervalTime(3000);
					static_cast<Enemy*>(pObject)->MoveTo(centerPos);
					static_cast<Enemy*>(pObject)->SpinLeft();
					static_cast<Enemy*>(pObject)->MoveTo(rightBottomPos);

					++spawnCount;
					spawnDelayTime = GetTickCount64();
				}

				if ( spawnCount == maxSpawnCount )
				{
					spawnCount = 0;
					spawnDelayTime = 0;
					bFinishedPattern = true;
				}
				break;
			}
			case eEnemySpawnPattern::RIGHT_TOP_TO_LEFT_BOTTOM_SPIN:
			{
				static ULONGLONG spawnDelayTime = 0;
				static int spawnCount = 0;
				int delay = 500;
				int maxSpawnCount = 5;

				Vector3 rightTopPos = Vector3(pOwner->GetPosition().x + (pOwner->GetScale().x * 0.5f),
											pOwner->GetPosition().y - (pOwner->GetScale().y * 0.3f));
				Vector3 leftBottomPos = Vector3(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f),
											pOwner->GetPosition().y + (pOwner->GetScale().y * 0.3f));
				Vector3 centerPos = Vector3(leftBottomPos.x + ((rightTopPos.x - leftBottomPos.x) * 0.5f),
											rightTopPos.y + ((leftBottomPos.y - rightTopPos.y) * 0.5f));

				// ** Spawn Count가 남았고 delay 시간이 지날때마다 스폰
				if ( spawnCount < maxSpawnCount && spawnDelayTime + delay < GetTickCount64() )
				{
					pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_NORMAL);
					pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
					pObject->SetTagName(eTagName::ENEMY_BLUE_ELF);
					pObject->SetPosition(rightTopPos);
					pObject->SetScale(40.0f, 40.0f);
					pObject->SetDirection(0.0f, 1.0f);
					pObject->SetSpeed(2.5f);
					pObject->SetBridge(pBridge);
					static_cast<Enemy*>(pObject)->SetEnemyType(eEnemyType::ENEMY_BLUE_ELF);
					static_cast<Enemy*>(pObject)->SetFireBulletIntervalTime(3000);
					static_cast<Enemy*>(pObject)->MoveTo(centerPos);
					static_cast<Enemy*>(pObject)->SpinRight();
					static_cast<Enemy*>(pObject)->MoveTo(leftBottomPos);

					++spawnCount;
					spawnDelayTime = GetTickCount64();
				}

				if ( spawnCount == maxSpawnCount )
				{
					spawnCount = 0;
					spawnDelayTime = 0;
					bFinishedPattern = true;
				}
				break;
			}
			case eEnemySpawnPattern::LEFT_BOTTOM_TO_RIGHT_TOP_SPIN:
			{
				static ULONGLONG spawnDelayTime = 0;
				static int spawnCount = 0;
				int delay = 500;
				int maxSpawnCount = 5;

				Vector3 rightTopPos = Vector3(pOwner->GetPosition().x + (pOwner->GetScale().x * 0.5f),
											pOwner->GetPosition().y - (pOwner->GetScale().y * 0.3f));
				Vector3 leftBottomPos = Vector3(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f),
											pOwner->GetPosition().y + (pOwner->GetScale().y * 0.3f));
				Vector3 centerPos = Vector3(leftBottomPos.x + ((rightTopPos.x - leftBottomPos.x) * 0.5f),
											rightTopPos.y + ((leftBottomPos.y - rightTopPos.y) * 0.5f));

				// ** Spawn Count가 남았고 delay 시간이 지날때마다 스폰
				if ( spawnCount < maxSpawnCount && spawnDelayTime + delay < GetTickCount64() )
				{
					pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_NORMAL);
					pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
					pObject->SetTagName(eTagName::ENEMY_GREEN_ELF);
					pObject->SetPosition(leftBottomPos);
					pObject->SetScale(40.0f, 40.0f);
					pObject->SetDirection(0.0f, 1.0f);
					pObject->SetSpeed(2.5f);
					pObject->SetBridge(pBridge);
					static_cast<Enemy*>(pObject)->SetEnemyType(eEnemyType::ENEMY_GREEN_ELF);
					static_cast<Enemy*>(pObject)->SetFireBulletIntervalTime(3000);
					static_cast<Enemy*>(pObject)->MoveTo(centerPos);
					static_cast<Enemy*>(pObject)->SpinLeft();
					static_cast<Enemy*>(pObject)->MoveTo(rightTopPos);

					++spawnCount;
					spawnDelayTime = GetTickCount64();
				}

				if ( spawnCount == maxSpawnCount )
				{
					spawnCount = 0;
					spawnDelayTime = 0;
					bFinishedPattern = true;
				}
				break;
			}
			case eEnemySpawnPattern::RIGHT_BOTTOM_TO_LEFT_TOP_SPIN:
			{
				static ULONGLONG spawnDelayTime = 0;
				static int spawnCount = 0;
				int delay = 500;
				int maxSpawnCount = 5;

				Vector3 leftTopPos = Vector3(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f),
											pOwner->GetPosition().y - (pOwner->GetScale().y * 0.3f));
				Vector3 rightBottomPos = Vector3(pOwner->GetPosition().x + (pOwner->GetScale().x * 0.5f),
											pOwner->GetPosition().y + (pOwner->GetScale().y * 0.3f));
				Vector3 centerPos = Vector3(leftTopPos.x + ((rightBottomPos.x - leftTopPos.x) * 0.5f),
											leftTopPos.y + ((rightBottomPos.y - leftTopPos.y) * 0.5f));

				// ** Spawn Count가 남았고 delay 시간이 지날때마다 스폰
				if ( spawnCount < maxSpawnCount && spawnDelayTime + delay < GetTickCount64() )
				{
					// ** 마지막 위치에 WHITE_ELF Enemy를 넣어줌
					if ( spawnCount == maxSpawnCount - 1 )
					{
						pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_NORMAL);
						pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
						pObject->SetTagName(eTagName::ENEMY_WHITE_ELF);
						pObject->SetPosition(rightBottomPos);
						pObject->SetScale(60.0f, 60.0f);
						pObject->SetDirection(0.0f, 1.0f);
						pObject->SetSpeed(2.5f);
						pObject->SetBridge(pBridge);
						static_cast<Enemy*>(pObject)->SetEnemyType(eEnemyType::ENEMY_WHITE_ELF);
						static_cast<Enemy*>(pObject)->SetFireBulletIntervalTime(3000);
						static_cast<Enemy*>(pObject)->MoveTo(centerPos);
						static_cast<Enemy*>(pObject)->SpinRight();
						static_cast<Enemy*>(pObject)->MoveTo(leftTopPos);
					}
					else
					{
						pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_NORMAL);
						pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
						pObject->SetTagName(eTagName::ENEMY_GREEN_ELF);
						pObject->SetPosition(rightBottomPos);
						pObject->SetScale(40.0f, 40.0f);
						pObject->SetDirection(0.0f, 1.0f);
						pObject->SetSpeed(2.5f);
						pObject->SetBridge(pBridge);
						static_cast<Enemy*>(pObject)->SetEnemyType(eEnemyType::ENEMY_GREEN_ELF);
						static_cast<Enemy*>(pObject)->SetFireBulletIntervalTime(3000);
						static_cast<Enemy*>(pObject)->MoveTo(centerPos);
						static_cast<Enemy*>(pObject)->SpinRight();
						static_cast<Enemy*>(pObject)->MoveTo(leftTopPos);
					}

					++spawnCount;
					spawnDelayTime = GetTickCount64();
				}

				if ( spawnCount == maxSpawnCount )
				{
					spawnCount = 0;
					spawnDelayTime = 0;
					bFinishedPattern = true;
				}
				break;
			}
			case eEnemySpawnPattern::FALLDOWN_GO_RAND:
			{
				bFinishedPattern = true;
				break;
			}
			case eEnemySpawnPattern::FALLDOWN_GO_ACCELERATION_RAND:
			{
				bFinishedPattern = true;
				break;
			}
			case eEnemySpawnPattern::FALLDOWN_GO_AND_SPIN:
			{
				bFinishedPattern = true;
				break;
			}
			case eEnemySpawnPattern::FALLDOWN_BACK_AND_FORTH:
			{
				bFinishedPattern = true;
				break;
			}
		}		

		// ** 해당 패턴이 종료되었다면 리스트에서 삭제
		if ( bFinishedPattern )
			readyPatternList.erase(listIter++);
		else
			++listIter;
	}
}

void EnemySpawnPatternScript::Update()
{
}