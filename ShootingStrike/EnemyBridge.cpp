#include "EnemyBridge.h"

EnemyBridge::EnemyBridge()
	: pImage(nullptr)
	, TransInfo(Transform())
	, Speed(0.0f)
{
}

EnemyBridge::~EnemyBridge()
{
}

void EnemyBridge::ReceiveInfoFromOwner()
{
	pImage = pOwner->GetImage();
	TransInfo = pOwner->GetTransInfo();
	Speed = pOwner->GetSpeed();
}

void EnemyBridge::SendInfoToOwner()
{
	pOwner->SetTransInfo(TransInfo);
	pOwner->SetSpeed(Speed);
}