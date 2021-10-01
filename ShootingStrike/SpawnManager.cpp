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

void SpawnManager::SpawnBullet(Object* _pOwner, Transform _transInfo, float _speed, int _damage, eBulletType _bulletType)
{
	Bridge* pBridge = nullptr;

	switch ( _bulletType )
	{
		case eBulletType::NORMAL: 
			pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::BULLET_NORMAL);	
			break;
		case eBulletType::GUIDE:  
			pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::BULLET_GUIDE);
			break;
		default: 
			break;
	}
	//pRightSideBackground->SetImageOffsetOrder(Point(1, 0));
	Bullet* pBullet = static_cast<Bullet*>(ObjectManager::GetInstance()->NewObject(eObjectKey::BULLET));
	pBullet->SetBridge(pBridge);
	pBullet->SetImage(eImageKey::BULLET);
	pBullet->SetOwner(_pOwner);
	pBullet->SetTransInfo(_transInfo);
	pBullet->SetSpeed(_speed);
	pBullet->SetDamage(_damage);
}

void SpawnManager::SpawnEnemy(Vector3 _position, Vector3 _direction, Bridge* _pBridge)
{
}
