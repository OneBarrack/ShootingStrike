#include "SpawnManager.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Effect.h"
#include "NormalBullet.h"
#include "GuideBullet.h"
#include "ExplosionEffect.h"

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
	pBullet->SetImage(eImageKey::BULLET);
	pBullet->SetOwner(_pOwner);
	pBullet->SetTransInfo(_transInfo);
	pBullet->SetSpeed(_speed);
	pBullet->SetDamage(_damage);
	pBullet->SetBridge(pBridge);
}

void SpawnManager::SpawnEnemy(Transform _transInfo, eBridgeKey _bridgeKey)
{
}

void SpawnManager::SpawnEffect(Transform _transInfo, eBridgeKey _bridgeKey)
{	
	Bridge* pBridge = nullptr;
	eImageKey imageKey;

	switch ( _bridgeKey )
	{
		case eBridgeKey::EFFECT_EXPLOSION:
			pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::EFFECT_EXPLOSION);
			imageKey = eImageKey::EXPLOSION;
			break;
		case eBridgeKey::EFFECT_HIT:
			pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::EFFECT_HIT);
			imageKey = eImageKey::HIT;
			break;
		default:
			return;
			break;
	}	

	Effect* pEffect = static_cast<Effect*>(ObjectManager::GetInstance()->NewObject(eObjectKey::EFFECT));
	pEffect->SetImage(imageKey);
	pEffect->SetTransInfo(_transInfo);
	pEffect->SetBridge(pBridge);
}

