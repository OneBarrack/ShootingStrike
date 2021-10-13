#include "EnemySpawnPatternScript.h"
#include "Object.h"
#include "ObjectManager.h"
#include "SpawnManager.h"
#include "MathManager.h"
#include "BackAndForthEnemy.h"
#include "GoAndSpinEnemy.h"
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
	readyPatternQueue = queue<pair<Object*, eEnemySpawnPattern>>();
}

void EnemySpawnPatternScript::ReadyToSpawn(Object* _pOwner, eEnemySpawnPattern _spawnPattern)
{
	readyPatternQueue.push(make_pair(_pOwner, _spawnPattern));
}

void EnemySpawnPatternScript::Run()
{
	Spawn();
	Update();
}

void EnemySpawnPatternScript::Spawn()
{
	while ( !readyPatternQueue.empty() )
	{
		Bridge* pBridge = nullptr;
		Object* pObject = nullptr;

		Object* pOwner = readyPatternQueue.front().first;
		eEnemySpawnPattern spawnPattern = readyPatternQueue.front().second;
		readyPatternQueue.pop();		

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
				static_cast<Enemy*>(pObject)->SetDestPosition(Vector3(pObject->GetPosition().x, pObject->GetPosition().y + 100.0f));
				break;
			}
			case eEnemySpawnPattern::FALLDOWN_GO_RAND:
			{
				float startPosX = (pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f) + 40.0f) + (rand() % static_cast<int>(pOwner->GetScale().x) - 80.0f);
				float destPosX  = (pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f) + 40.0f) + (rand() % static_cast<int>(pOwner->GetScale().x) - 80.0f);

				pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_NORMAL);
				pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
				pObject->SetPosition(startPosX, 0.0f);
				pObject->SetScale(40.0f, 40.0f);
				pObject->SetDirection(0.0f, 1.0f);
				pObject->SetSpeed(0.75f);
				pObject->SetBridge(pBridge);
				static_cast<Enemy*>(pObject)->SetFireBulletIntervalTime(3000);
				static_cast<Enemy*>(pObject)->SetDestPosition(Vector3(destPosX, WINDOWS_HEIGHT * 0.75f));
				break;
			}
			case eEnemySpawnPattern::FALLDOWN_GO_ACCELERATION_RAND:
			{
				float posX = (pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f) + 40.0f) + (rand() % static_cast<int>(pOwner->GetScale().x - 80.0f));

				pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_NORMAL);
				pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
				pObject->SetPosition(posX, 0.0f);
				pObject->SetScale(40.0f, 40.0f);
				pObject->SetDirection(0.0f, 1.0f);
				pObject->SetSpeed(0.75f);
				pObject->SetBridge(pBridge);
				pObject->SetAcceleration(0.1f);
				static_cast<Enemy*>(pObject)->SetFireBulletIntervalTime(3000);
				static_cast<Enemy*>(pObject)->SetDestPosition(Vector3(pObject->GetPosition().x, pObject->GetPosition().y + 100.0f));
				break;
			}
			case eEnemySpawnPattern::FALLDOWN_GO_AND_SPIN:
			{
				pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_GO_AND_SPIN);
				pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
				pObject->SetPosition(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.25f), 0.0f);
				pObject->SetScale(40.0f, 40.0f);
				pObject->SetDirection(0.0f, 1.0f);
				pObject->SetSpeed(0.75f);
				pObject->SetBridge(pBridge);
				static_cast<Enemy*>(pObject)->SetFireBulletIntervalTime(3000);
				static_cast<Enemy*>(pObject)->SetDestPosition(Vector3(pObject->GetPosition().x, pObject->GetPosition().y + 100.0f));
				static_cast<Enemy*>(pObject)->SetStopAtDest(true);
				static_cast<GoAndSpinEnemy*>(pBridge)->RightSpin();

				pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_GO_AND_SPIN);
				pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
				pObject->SetPosition(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.1f), 0.0f);
				pObject->SetScale(40.0f, 40.0f);
				pObject->SetDirection(0.0f, 1.0f);
				pObject->SetSpeed(1.0f);
				pObject->SetBridge(pBridge);
				static_cast<Enemy*>(pObject)->SetFireBulletIntervalTime(2000);
				static_cast<Enemy*>(pObject)->SetDestPosition(Vector3(pObject->GetPosition().x, pObject->GetPosition().y + 300.0f));
				static_cast<Enemy*>(pObject)->SetStopAtDest(true);
				static_cast<GoAndSpinEnemy*>(pBridge)->RightSpin();

				pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_GO_AND_SPIN);
				pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
				pObject->SetPosition(pOwner->GetPosition().x + (pOwner->GetScale().x * 0.1f), 0.0f);
				pObject->SetScale(40.0f, 40.0f);
				pObject->SetDirection(0.0f, 1.0f);
				pObject->SetSpeed(1.0f);
				pObject->SetBridge(pBridge);
				static_cast<Enemy*>(pObject)->SetFireBulletIntervalTime(2000);
				static_cast<Enemy*>(pObject)->SetDestPosition(Vector3(pObject->GetPosition().x, pObject->GetPosition().y + 300.0f));
				static_cast<Enemy*>(pObject)->SetStopAtDest(true);
				static_cast<GoAndSpinEnemy*>(pBridge)->LeftSpin();

				pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_GO_AND_SPIN);
				pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
				pObject->SetPosition(pOwner->GetPosition().x + (pOwner->GetScale().x * 0.25f), 0.0f);
				pObject->SetScale(40.0f, 40.0f);
				pObject->SetDirection(0.0f, 1.0f);
				pObject->SetSpeed(0.75f);
				pObject->SetBridge(pBridge);
				static_cast<Enemy*>(pObject)->SetFireBulletIntervalTime(3000);
				static_cast<Enemy*>(pObject)->SetDestPosition(Vector3(pObject->GetPosition().x, pObject->GetPosition().y + 100.0f));
				static_cast<Enemy*>(pObject)->SetStopAtDest(true);
				static_cast<GoAndSpinEnemy*>(pBridge)->LeftSpin();
				break;
			}
			case eEnemySpawnPattern::FALLDOWN_BACK_AND_FORTH:
			{
				pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_BACK_AND_FORTH);
				pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
				pObject->SetPosition(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.25f), 0.0f);
				pObject->SetScale(40.0f, 40.0f);
				pObject->SetDirection(0.0f, 1.0f);
				pObject->SetSpeed(0.75f);
				pObject->SetBridge(pBridge);
				static_cast<Enemy*>(pObject)->SetFireBulletIntervalTime(3000);
				static_cast<Enemy*>(pObject)->SetDestPosition(Vector3(pObject->GetPosition().x, pObject->GetPosition().y + 100.0f));
				static_cast<BackAndForthEnemy*>(pBridge)->RightSpin();

				pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_BACK_AND_FORTH);
				pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
				pObject->SetPosition(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.1f), 0.0f);
				pObject->SetScale(40.0f, 40.0f);
				pObject->SetDirection(0.0f, 1.0f);
				pObject->SetSpeed(1.0f);
				pObject->SetBridge(pBridge);
				static_cast<Enemy*>(pObject)->SetFireBulletIntervalTime(2000);
				static_cast<Enemy*>(pObject)->SetDestPosition(Vector3(pObject->GetPosition().x, pObject->GetPosition().y + 300.0f));
				static_cast<BackAndForthEnemy*>(pBridge)->RightSpin();

				pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_BACK_AND_FORTH);
				pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
				pObject->SetPosition(pOwner->GetPosition().x + (pOwner->GetScale().x * 0.1f), 0.0f);
				pObject->SetScale(40.0f, 40.0f);
				pObject->SetDirection(0.0f, 1.0f);
				pObject->SetSpeed(1.0f);
				pObject->SetBridge(pBridge);
				static_cast<Enemy*>(pObject)->SetFireBulletIntervalTime(2000);
				static_cast<Enemy*>(pObject)->SetDestPosition(Vector3(pObject->GetPosition().x, pObject->GetPosition().y + 300.0f));
				static_cast<BackAndForthEnemy*>(pBridge)->LeftSpin();

				pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::ENEMY_BACK_AND_FORTH);
				pObject = ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY);
				pObject->SetPosition(pOwner->GetPosition().x + (pOwner->GetScale().x * 0.25f), 0.0f);
				pObject->SetScale(40.0f, 40.0f);
				pObject->SetDirection(0.0f, 1.0f);
				pObject->SetSpeed(0.75f);
				pObject->SetBridge(pBridge);
				static_cast<Enemy*>(pObject)->SetFireBulletIntervalTime(3000);
				static_cast<Enemy*>(pObject)->SetDestPosition(Vector3(pObject->GetPosition().x, pObject->GetPosition().y + 100.0f));
				static_cast<BackAndForthEnemy*>(pBridge)->LeftSpin();
				break;
			}
		}		
	}
}

void EnemySpawnPatternScript::Update()
{
}