#include "BossEnemy.h"
#include "Object.h"
#include "BitmapManager.h"
#include "SpawnManager.h"
#include "InputManager.h"

BossEnemy::BossEnemy()
{
}

BossEnemy::~BossEnemy()
{
	Release();
}


void BossEnemy::Initialize()
{
	Key = eBridgeKey::ENEMY_BOSS;
}

void BossEnemy::Update()
{
	// ** Owner의 데이터를 받아옴
	ReceiveInfoFromOwner();

	static int PatternIndex = 0;
	static int ActiveCount = 0;	
	static ULONGLONG ActiveTime = GetTickCount64();

	if ( CheckKeyInputState(eInputKey::KEY_LBUTTON, eKeyInputState::DOWN) )
	{
		PatternIndex = 1;
		ActiveCount = 1;
		ActiveTime = GetTickCount64();
	}

	switch ( PatternIndex )
	{
		case 1:
		{
			int MaxActiveCount = 50;

			// ** Level 만큼 총알 숫자를 늘리고, 상방 기준 총알 간 간격에 대한 각도를 설정하여
			// ** 부채꼴 형태로 발사되도록 한다.
			// ** angleGap : 총알간 간격 각도

			int AngleGap = 30;
			if ( ActiveTime + 50 < GetTickCount64() )
			{				
				int BulletCount = 360 / AngleGap;				
				for ( int i = 0; i < BulletCount; ++i )
				{
					// ** 상방 기준 현재 각도
					int Angle = AngleGap * i + (ActiveCount * 7);

					// ** Bullet의 TransInfo 설정
					Transform BulletTransInfo;
					BulletTransInfo.Position = TransInfo.Position;
					BulletTransInfo.Scale = Vector3(10.0f, 10.0f);
					BulletTransInfo.Direction = Vector3(cosf(Angle * PI / 180), -sinf(Angle * PI / 180));

					// ** Bullet의 Speed 설정
					float BulletSpeed = 3.0f;

					// ** Bullet Spawn
					SpawnManager::SpawnBullet(pOwner, BulletTransInfo, BulletSpeed, 1, eBulletFiringType::NORMAL);
				}
								
				ActiveTime = GetTickCount64();
				++ActiveCount;
			}
			if ( MaxActiveCount < ActiveCount )
			{
				PatternIndex = 0;
			}
			break;
		}
		default:
			ActiveTime = 0;
			break;
	}

	//TransInfo.Position.x += TransInfo.Direction.x * Speed;
	//TransInfo.Position.y += TransInfo.Direction.y * Speed;

	// ** Owner로 가공된 데이터 전달
	SendInfoToOwner();
}


void BossEnemy::Render(HDC _hdc)
{
	Bitmap* pImage = pOwner->GetImage();
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

void BossEnemy::Release()
{

}
