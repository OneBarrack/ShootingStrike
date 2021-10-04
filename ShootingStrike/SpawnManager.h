#pragma once
#include "Headers.h"

class Object;
class SpawnManager
{
public:
	static void SpawnPlayer();
	static void SpawnBullet(Object* _pOwner, Transform _transInfo, float _speed, int _Damage, eBulletType _bulletType);
	static void SpawnEnemy(Transform _transInfo, eBridgeKey _bridgeKey);
	static void SpawnEffect(Transform _transInfo, eBridgeKey _bridgeKey);
};

