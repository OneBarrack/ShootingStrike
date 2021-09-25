#pragma once
#include "Headers.h"

class Object;
class Bridge;
class SpawnManager
{
public:
	static void SpawnPlayer();
	static void SpawnBullet(Object* _pOwner, Transform _TransInfo, Bridge* _pBridge, float _Speed, int _Damage);
	static void SpawnEnemy(Vector3 _Position, Vector3 _Direction, Bridge* _pBridge);
};

