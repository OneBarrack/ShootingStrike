#include "SpawnManager.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "NormalBullet.h"
#include "GuideBullet.h"

void SpawnManager::SpawnPlayer()
{
	Player* pPlayer = static_cast<Player*>(ObjectManager::GetInstance()->GetPlayer());
	pPlayer->SetStatus(eObjectStatus::ACTIVATED);
	pPlayer->Spawn();
}

void SpawnManager::SpawnBullet(Object* _pOwner, Transform _TransInfo, float _Speed, int _Damage, eBulletFiringType _FiringType)
{
	Bridge* pBridge = nullptr;

	switch ( _FiringType )
	{
		case eBulletFiringType::NORMAL: 
			pBridge = ObjectManager::GetInstance()->TakeBridge(eBridgeKey::BULLET_NORMAL);	
			break;
		case eBulletFiringType::GUIDE:  
			pBridge = ObjectManager::GetInstance()->TakeBridge(eBridgeKey::BULLET_GUIDE);
			break;
		default: 
			break;
	}
	//pRightSideBackground->SetImageOffsetOrder(Point(1, 0));
	Bullet* pBullet = static_cast<Bullet*>(ObjectManager::GetInstance()->TakeObject(eObjectKey::BULLET));
	pBullet->SetBridge(pBridge);
	pBullet->SetImage(eImageKey::BULLET);
	pBullet->SetOwner(_pOwner);
	pBullet->SetTransInfo(_TransInfo);
	pBullet->SetSpeed(_Speed);
	pBullet->SetDamage(_Damage);
}

void SpawnManager::SpawnEnemy(Vector3 _Position, Vector3 _Direction, Bridge* _pBridge)
{
}
