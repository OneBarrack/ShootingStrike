#include "EnemyBridge.h"

EnemyBridge::EnemyBridge()
	: pImage(nullptr)
	, transInfo(Transform())
	, speed(0.0f)
{
}

EnemyBridge::~EnemyBridge()
{
}

void EnemyBridge::ReceiveInfoFromOwner()
{
	pImage = pOwner->GetImage();
	transInfo = pOwner->GetTransInfo();
	speed = pOwner->GetSpeed();
}

void EnemyBridge::SendInfoToOwner()
{
	pOwner->SetTransInfo(transInfo);
	pOwner->SetSpeed(speed);
}