#include "SpawnManager.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

void SpawnManager::SpawnBullet(Object* Owner, Vector3 _Position, Vector3 _Direction, Bridge* _pBridge, int _Damage)
{
	Bullet* pBullet = static_cast<Bullet*>(ObjectManager::GetInstance()->TakeObject(eObjectKey::BULLET, _Position, _pBridge));
	pBullet->SetOwner(Owner);
	pBullet->SetDirection(_Direction);
	pBullet->SetDamage(_Damage);
}

void SpawnManager::SpawnEnemy(Vector3 _Position, Vector3 _Direction, Bridge* _pBridge)
{
}
