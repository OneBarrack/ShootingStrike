#include "SpawnManager.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

void SpawnManager::SpawnBullet(Object* _pOwner, Transform _TransInfo, Bridge* _pBridge, float _Speed, int _Damage)
{
	Bullet* pBullet = static_cast<Bullet*>(ObjectManager::GetInstance()->TakeObject(eObjectKey::BULLET, _pBridge));
	pBullet->SetOwner(_pOwner);
	pBullet->SetTransInfo(_TransInfo);
	pBullet->SetSpeed(_Speed);
	pBullet->SetDamage(_Damage);
}

void SpawnManager::SpawnEnemy(Vector3 _Position, Vector3 _Direction, Bridge* _pBridge)
{
}
