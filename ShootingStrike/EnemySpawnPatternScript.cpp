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
			case eEnemySpawnPattern::FALLDOWN_GO:
			{
				pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_NORMAL);
				pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
				pObject->SetPosition(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.25f), 0.0f);
				pObject->SetScale(40.0f, 40.0f);
				pObject->SetDirection(0.0f, 1.0f);
				pObject->SetSpeed(0.75f);
				pObject->SetBridge(pBridge);
				static_cast<Enemy*>(pObject)->SetFireBulletIntervalTime(3000);
				//static_cast<Enemy*>(pObject)->SetDestPosition(Vector3(pObject->GetPosition().x, pObject->GetPosition().y + 100.0f));
				//static_cast<Enemy*>(pObject)->MoveTo(Vector3(pObject->GetPosition().x, pObject->GetPosition().y + 100.0f));
				//static_cast<Enemy*>(pObject)->SetDestPosition(Vector3(pObject->GetPosition().x + 100.0f, pObject->GetPosition().y + 100.0f));
				//static_cast<Enemy*>(pObject)->MoveTo(Vector3(pObject->GetPosition().x + 100.0f, pObject->GetPosition().y + 100.0f));

				static_cast<Enemy*>(pObject)->BackAndForthLeft();
				//static_cast<Enemy*>(pObject)->SpinLeft();
				//static_cast<Enemy*>(pObject)->SpinRight();
				//static_cast<Enemy*>(pObject)->MoveTo(Vector3(pObject->GetPosition().x, pObject->GetPosition().y + 200.0f));
				//static_cast<Enemy*>(pObject)->SpinLeft(true);

				/*pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_NORMAL);
				pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
				pObject->SetPosition(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.25f), 0.0f);
				pObject->SetScale(40.0f, 40.0f);
				pObject->SetDirection(0.0f, 1.0f);
				pObject->SetSpeed(0.75f);
				pObject->SetBridge(pBridge);
				static_cast<Enemy*>(pObject)->SetFireBulletIntervalTime(3000);
				static_cast<Enemy*>(pObject)->SetDestPosition(Vector3(pObject->GetPosition().x, pObject->GetPosition().y + 100.0f));

				pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_NORMAL);
				pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
				pObject->SetPosition(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.1f), 0.0f);
				pObject->SetScale(40.0f, 40.0f);
				pObject->SetDirection(0.0f, 1.0f);
				pObject->SetSpeed(1.0f);
				pObject->SetBridge(pBridge);
				static_cast<Enemy*>(pObject)->SetFireBulletIntervalTime(2000);
				static_cast<Enemy*>(pObject)->SetDestPosition(Vector3(pObject->GetPosition().x, pObject->GetPosition().y + 300.0f));

				pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_NORMAL);
				pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
				pObject->SetPosition(pOwner->GetPosition().x + (pOwner->GetScale().x * 0.1f), 0.0f);
				pObject->SetScale(40.0f, 40.0f);
				pObject->SetDirection(0.0f, 1.0f);
				pObject->SetSpeed(1.0f);
				pObject->SetBridge(pBridge);
				static_cast<Enemy*>(pObject)->SetFireBulletIntervalTime(2000);
				static_cast<Enemy*>(pObject)->SetDestPosition(Vector3(pObject->GetPosition().x, pObject->GetPosition().y + 300.0f));

				pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_NORMAL);
				pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
				pObject->SetPosition(pOwner->GetPosition().x + (pOwner->GetScale().x * 0.25f), 0.0f);
				pObject->SetScale(40.0f, 40.0f);
				pObject->SetDirection(0.0f, 1.0f);
				pObject->SetSpeed(0.75f);
				pObject->SetBridge(pBridge);
				static_cast<Enemy*>(pObject)->SetFireBulletIntervalTime(3000);
				static_cast<Enemy*>(pObject)->SetDestPosition(Vector3(pObject->GetPosition().x, pObject->GetPosition().y + 100.0f));*/
				
				bFinishedPattern = true;
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