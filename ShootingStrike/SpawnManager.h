#pragma once
#include "Headers.h"

class Object;
class Bridge;
class SpawnManager
{
public:
	static void SpawnPlayer();
	static void SpawnBullet(Object* _pOwner, Transform _transInfo, float _speed, int _Damage, eBulletType _bulletType);
	static void SpawnEnemy(Vector3 _position, Vector3 _direction, Bridge* _pBridge);
};

