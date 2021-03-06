#include "SpawnManager.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Effect.h"
#include "NormalBullet.h"
#include "GuideBullet.h"
#include "ExplosionEffect.h"
#include "BitmapManager.h"

Object* SpawnManager::SpawnPlayer()
{
	Player* pPlayer = static_cast<Player*>(ObjectManager::GetInstance()->GetPlayer());
	pPlayer->Initialize();
	pPlayer->SetStatus(eObjectStatus::ACTIVATED);
	pPlayer->Spawn();

	return pPlayer;
}

Object* SpawnManager::SpawnBullet(Object* _pOwner, Transform _transInfo, float _speed, int _damage, eBridgeKey _bridgeKey)
{
	Bullet* pBullet = nullptr;
	Bridge* pBridge = nullptr;

	switch ( _bridgeKey )
	{
		case eBridgeKey::BULLET_NORMAL:
			pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::BULLET_NORMAL);	
			break;
		case eBridgeKey::BULLET_GUIDE:
			pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::BULLET_GUIDE);
			break;
		default:
			return pBullet;
			break;
	}
	//pRightSideBackground->SetImageOffsetOrder(Point(1, 0));
	pBullet = static_cast<Bullet*>(ObjectManager::GetInstance()->NewObject(eObjectKey::BULLET));
	pBullet->SetImage(eImageKey::BULLET);
	pBullet->SetOwner(_pOwner);
	pBullet->SetTransInfo(_transInfo);
	pBullet->SetSpeed(_speed);
	pBullet->SetDamage(_damage);
	pBullet->SetBridge(pBridge);

	return pBullet;
}

Object* SpawnManager::SpawnBullet(Object* _pOwner, Transform _transInfo, float _speed, int _damage, Bridge* _pBridge)
{
	Bullet* pBullet = nullptr;
	eBridgeKey bridgeKey = _pBridge->GetKey();

	if ( bridgeKey == eBridgeKey::BULLET_NORMAL ||
		bridgeKey == eBridgeKey::BULLET_GUIDE )
	{
		pBullet = static_cast<Bullet*>(ObjectManager::GetInstance()->NewObject(eObjectKey::BULLET));
		pBullet->SetImage(eImageKey::BULLET);
		pBullet->SetOwner(_pOwner);
		pBullet->SetTransInfo(_transInfo);
		pBullet->SetSpeed(_speed);
		pBullet->SetDamage(_damage);
		pBullet->SetBridge(_pBridge);
	}

	return pBullet;
}

Object* SpawnManager::SpawnEnemy(eTagName _tagName, Transform _transInfo, float _speed, Bridge* _pBridge)
{
	Enemy* pEnemy = nullptr;
	eBridgeKey bridgeKey = _pBridge->GetKey();

	eImageKey imageKey;
	switch ( bridgeKey )
	{
		case eBridgeKey::ENEMY_NORMAL:	imageKey = eImageKey::ENEMY_NORMAL;	break;
		case eBridgeKey::ENEMY_BOSS:	imageKey = eImageKey::ENEMY_ANGEL;	break;
		default:
			return nullptr;
			break;
	}

	pEnemy = static_cast<Enemy*>(ObjectManager::GetInstance()->NewObject(eObjectKey::ENEMY));
	pEnemy->SetImage(imageKey);
	pEnemy->SetTransInfo(_transInfo);
	pEnemy->SetSpeed(_speed);
	pEnemy->SetTagName(_tagName);
	pEnemy->SetBridge(_pBridge);

	return pEnemy;
}

Object* SpawnManager::SpawnEffect(Transform _transInfo, eBridgeKey _bridgeKey)
{	
	Effect* pEffect = nullptr;
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
			return pEffect;
			break;
	}	

	pEffect = static_cast<Effect*>(ObjectManager::GetInstance()->NewObject(eObjectKey::EFFECT));
	pEffect->SetImage(imageKey);
	pEffect->SetTransInfo(_transInfo);
	pEffect->SetBridge(pBridge);

	return pEffect;
}

