#include "HitEffect.h"

HitEffect::HitEffect()
	: segmentImageCount(0)
	, offset(0)
	, delay(0)
	, time(0)
{

}

HitEffect::~HitEffect()
{
}


void HitEffect::Initialize()
{
	Super::Initialize();

	if ( pImage )
		segmentImageCount = pImage->GetScale().x / pImage->GetSegmentationScale().x;
	else
		segmentImageCount = 1;

	key = eBridgeKey::EFFECT_HIT;
	time = GetTickCount64();
	offset = 0;
	delay = 100;
}

void HitEffect::Update()
{
	Super::Update();
}

void HitEffect::Render(HDC _hdc)
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
		RGB(0, 63, 128));

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

void HitEffect::Release()
{
	Super::Release();
}