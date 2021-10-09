#include "ExplosionEffect.h"

ExplosionEffect::ExplosionEffect()
	: offset(0)
	, delay(0)
	, time(0)
{

}

ExplosionEffect::~ExplosionEffect()
{
}


void ExplosionEffect::Initialize()
{
	Super::Initialize();	
		
	segmentImageCount = 1;
	key = eBridgeKey::EFFECT_EXPLOSION;
	time = GetTickCount64();
	offset = 0;
	delay = 100;
}

void ExplosionEffect::Update()
{
	Super::Update();

	ReceiveInfoFromOwner();
	SendInfoToOwner();
}

void ExplosionEffect::Render(HDC _hdc)
{
	Super::Render(_hdc);	

	if ( !pImage )
		return;	

	TransparentBlt(_hdc,
		(int)(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
		(int)(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
		(int)(pOwner->GetScale().x),
		(int)(pOwner->GetScale().y),
		pImage->GetMemDC(),
		(int)(pImage->GetSegmentationScale().x * offset),
		0,
		(int)(pImage->GetSegmentationScale().x),
		(int)(pImage->GetSegmentationScale().y),
		RGB(255, 0, 255));

	// ** Delay 시간 주기로 Offset 증가
	if ( time + delay < GetTickCount64() )
	{
		time = GetTickCount64();

		// ** 폭발 후 사라지도록.
		if ( ++offset == segmentImageCount )
		{
			offset = 0;
			pOwner->SetStatus(eObjectStatus::DESTROYED);
		}			
	}	
}

void ExplosionEffect::Release()
{
	Super::Release();
}