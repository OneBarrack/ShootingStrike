#pragma once
#include "Headers.h"

class Object;
class Bridge;
class SpawnManager
{
public:
	static Object* SpawnPlayer();
	static Object* SpawnBullet(Object* _pOwner, Transform _transInfo, float _speed, int _damage, eBridgeKey _bridgeKey);
	static Object* SpawnBullet(Object* _pOwner, Transform _transInfo, float _speed, int _damage, Bridge* _pBridge);
	static Object* SpawnEnemy(Transform _transInfo, eBridgeKey _bridgeKey);
	static Object* SpawnEffect(Transform _transInfo, eBridgeKey _bridgeKey);
};

