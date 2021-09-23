#pragma once
#include "Headers.h"

class Object;
class Bridge;
class SpawnManager
{
public:
	static void SpawnBullet(Object* Owner, Vector3 _Position, Vector3 _Direction, Bridge* _pBridge, int _Damage);
	static void SpawnEnemy(Vector3 _Position, Vector3 _Direction, Bridge* _pBridge);
};

