#include "MapProgressUI.h"
#include "BitmapManager.h"
#include "RenderManager.h"
#include "GameDataManager.h"

MapProgressUI::MapProgressUI()
	: pPlayerImage(nullptr)
	, mapProgressRatio(0.0f)
{

}

MapProgressUI::~MapProgressUI()
{
}


void MapProgressUI::Initialize()
{
	Super::Initialize();

	pPlayerImage = BitmapManager::GetInstance()->GetImage(eImageKey::PLAYER);
	mapProgressRatio = 0.0f;

	key = eBridgeKey::UI_MAP_PROGRESS;
}

void MapProgressUI::Update()
{
	Super::Update();

	mapProgressRatio = GameDataManager::GetInstance()->GetMapProgressRatio();
}

void MapProgressUI::Render(HDC _hdc)
{
	Super::Render(_hdc);

	if ( !pPlayerImage )
		return;
	
	// ** Box
	RenderManager::DrawRect(_hdc, pOwner->GetTransInfo(), RGB(255, 0, 0));
	
	TransparentBlt(_hdc,
		int(pOwner->GetPosition().x - 40.0f),
		int((pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f) - 40.0f) +
			(pOwner->GetScale().y * (1.0f - mapProgressRatio))),
		int(80.0f),
		int(80.0f),
		pPlayerImage->GetMemDC(),
		int(pPlayerImage->GetSegmentationScale().x),
		int(0),
		int(pPlayerImage->GetSegmentationScale().x),
		int(pPlayerImage->GetSegmentationScale().y),
		RGB(255, 0, 255));
}

void MapProgressUI::Release()
{
	Super::Release();

	pPlayerImage = nullptr;
}