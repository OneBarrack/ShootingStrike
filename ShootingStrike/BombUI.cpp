#include "BombUI.h"
#include "BitmapManager.h"
#include "ObjectManager.h"
#include "GameDataManager.h"
#include "Player.h"

BombUI::BombUI()
	: pItemImage(nullptr)
	, bombCount(0)
{
}

BombUI::~BombUI()
{
}


void BombUI::Initialize()
{
	Super::Initialize();

	if ( !pItemImage )
		pItemImage = BitmapManager::GetInstance()->GetImage(eImageKey::ITEM);

	key = eBridgeKey::UI_BOMB;
	bombCount = 0;
}

void BombUI::Update()
{
	Super::Update();

	Player* pPlayer = static_cast<Player*>(ObjectManager::GetInstance()->GetPlayer());
	if ( pPlayer )
		bombCount = pPlayer->GetBomb();
}

void BombUI::Render(HDC _hdc)
{
	Super::Render(_hdc);

	if ( !pItemImage )
		return;

	Point bombImageOffset = Point(3, 0);

	// ** Life 만큼 이미지 드로우
	for ( int offset = 0; offset < bombCount; ++offset )
	{
		// ** Owner의 Scale y 값을 이미지 사이즈로 지정. (현재 가로로 표시하는 방식만 적용)
		TransparentBlt(_hdc, // ** 최종 출력 위치
			int(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f) + (pOwner->GetScale().y * offset)),
			int(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
			int(pOwner->GetScale().y),
			int(pOwner->GetScale().y),
			pItemImage->GetMemDC(),
			int(pItemImage->GetSegmentationScale().x * bombImageOffset.x),
			int(pItemImage->GetSegmentationScale().y * bombImageOffset.y),
			int(pItemImage->GetSegmentationScale().x),
			int(pItemImage->GetSegmentationScale().y),
			RGB(255, 0, 255));
	}
}

void BombUI::Release()
{
	Super::Release();

	pItemImage = nullptr;
}