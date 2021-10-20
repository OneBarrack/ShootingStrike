#include "SpreadAfterDelayBullet.h"
#include "Object.h"
#include "Bullet.h"
#include "ObjectManager.h"
#include "SpawnManager.h"
#include "MathManager.h"

SpreadAfterDelayBullet::SpreadAfterDelayBullet()
	: time(0)
	, delay(0)
	, bDelayOver(false)
	, spreadCount(0)
	, bulletCount(0)
	, intervalAngle(0)
{
}

SpreadAfterDelayBullet::~SpreadAfterDelayBullet()
{
}


void SpreadAfterDelayBullet::Initialize()
{
	Super::Initialize();

	key = eBridgeKey::BULLET_SPREAD_AFTER_DELAY;

	time = GetTickCount64();
	delay = 1000;
	bDelayOver = false;

	spreadCount = 1;
	bulletCount = 1;
	intervalAngle = 30;
}

void SpreadAfterDelayBullet::Update()
{
	Super::Update();

	// ** Owner의 데이터를 받아옴
	ReceiveInfoFromOwner();

	if ( !bDelayOver && time + delay < GetTickCount64() )
	{
		Bullet* pOwnerBullet = static_cast<Bullet*>(pOwner);

		// 총알을 퍼뜨리며 생성
		if ( bulletCount > 0 )
		{
			float startAngle = -intervalAngle * 0.5f * (bulletCount - 1);

			for ( int i = 0; i < bulletCount; ++i )
			{				
				float angle = startAngle + (intervalAngle * i);

				// ** Bullet의 TransInfo 설정
				Transform bulletTransInfo;
				bulletTransInfo.Position = transInfo.Position;
				bulletTransInfo.Scale = transInfo.Scale;
				bulletTransInfo.Direction = MathManager::RotateByDegree(transInfo.Direction, angle);

				if ( spreadCount > 1 )
				{
					Bridge* pBridge = ObjectManager::GetInstance()->NewBridge(eBridgeKey::BULLET_SPREAD_AFTER_DELAY);
					static_cast<SpreadAfterDelayBullet*>(pBridge)->SetDelay(delay);
					static_cast<SpreadAfterDelayBullet*>(pBridge)->SetSpreadCount(spreadCount - 1);
					static_cast<SpreadAfterDelayBullet*>(pBridge)->SetBulletCount(bulletCount);
					static_cast<SpreadAfterDelayBullet*>(pBridge)->SetIntervalAngle(intervalAngle);

					SpawnManager::SpawnBullet(pOwnerBullet->GetOwner(), bulletTransInfo, speed, pOwnerBullet->GetDamage(), pBridge);
				}
				else
				{
					SpawnManager::SpawnBullet(pOwnerBullet->GetOwner(), bulletTransInfo, speed, pOwnerBullet->GetDamage(), eBridgeKey::BULLET_NORMAL);
				}
			}
		}
		bDelayOver = true;

		cout << spreadCount << endl;
		// 총알을 퍼뜨려 생성 후 삭제
		pOwner->SetStatus(eObjectStatus::DESTROYED);
	}

	transInfo.Position.x += transInfo.Direction.x * speed;
	transInfo.Position.y += transInfo.Direction.y * speed;

	// ** Owner로 가공된 데이터 전달
	SendInfoToOwner();
}


void SpreadAfterDelayBullet::Render(HDC _hdc)
{
	Super::Render(_hdc);

	if ( !pImage )
		return;

	TransparentBlt(_hdc,
		(int)(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
		(int)(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
		(int)(pOwner->GetScale().x),
		(int)(pOwner->GetScale().y),
		pOwner->GetImage()->GetMemDC(),
		(int)(pImage->GetSegmentationScale().x * pOwner->GetImageOffsetOrder().x),
		(int)(pImage->GetSegmentationScale().y * pOwner->GetImageOffsetOrder().y),
		(int)(pImage->GetSegmentationScale().x),
		(int)(pImage->GetSegmentationScale().y),
		RGB(255, 0, 255));
}

void SpreadAfterDelayBullet::Release()
{
	Super::Release();
}