#include "LifeUI.h"
#include "BitmapManager.h"
#include "ObjectManager.h"
#include "GameDataManager.h"
#include "Player.h"

LifeUI::LifeUI()
	: pPlayerImage(nullptr)
	, life(0)
{
}

LifeUI::~LifeUI()
{
}


void LifeUI::Initialize()
{
	Super::Initialize();
	
	if ( !pPlayerImage )
		pPlayerImage = ObjectManager::GetInstance()->GetPlayer()->GetImage();
	
	life = 0;
	key = eBridgeKey::UI_LIFE;
}

void LifeUI::Update()
{
	Super::Update();

	life = GameDataManager::GetInstance()->GetPlayerLife();
}

void LifeUI::Render(HDC _hdc)
{
	Super::Render(_hdc);

	if ( !pPlayerImage )
		return;
	
	// ** Life 만큼 이미지 드로우
	for ( int offset = 0; offset < life; ++offset )
	{
		// ** Owner의 Scale y 값을 이미지 사이즈로 지정. (현재 가로로 표시하는 방식만 적용)
		TransparentBlt(_hdc, // ** 최종 출력 위치
			int(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f) + (pOwner->GetScale().y * offset)),
			int(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
			int(pOwner->GetScale().y),
			int(pOwner->GetScale().y),
			pPlayerImage->GetMemDC(),
			int(pPlayerImage->GetSegmentationScale().x),
			int(0),
			int(pPlayerImage->GetSegmentationScale().x),
			int(pPlayerImage->GetSegmentationScale().y),
			RGB(255, 0, 255));
	}
}

void LifeUI::Release()
{
	Super::Release();

	pPlayerImage = nullptr;
}