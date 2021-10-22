#include "MapProgressUI.h"
#include "BitmapManager.h"
#include "RenderManager.h"
#include "GameDataManager.h"
#include "ObjectManager.h"

MapProgressUI::MapProgressUI()
	: pBkgImage(nullptr)
	, pPlayerImage(nullptr)
	, mapProgressRatio(0.0f)
{

}

MapProgressUI::~MapProgressUI()
{
}


void MapProgressUI::Initialize()
{
	Super::Initialize();

	pBkgImage = ObjectManager::GetInstance()->FindObjectWithTag(eTagName::STAGE_MAIN_BKG)->GetImage();
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
	
	// ** Bkg image
	TransparentBlt(_hdc,
		int(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
		int(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
		int(pOwner->GetScale().x),
		int(pOwner->GetScale().y * 0.25f),
		pBkgImage->GetMemDC(),
		int(0),
		int(0),
		int(pBkgImage->GetSegmentationScale().x),
		int(pBkgImage->GetSegmentationScale().y),
		RGB(255, 0, 255));

	TransparentBlt(_hdc,
		int(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
		int(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.25f)),
		int(pOwner->GetScale().x),
		int(pOwner->GetScale().y * 0.25f),
		pBkgImage->GetMemDC(),
		int(0),
		int(0),
		int(pBkgImage->GetSegmentationScale().x),
		int(pBkgImage->GetSegmentationScale().y),
		RGB(255, 0, 255));

	TransparentBlt(_hdc,
		int(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
		int(pOwner->GetPosition().y),
		int(pOwner->GetScale().x),
		int(pOwner->GetScale().y * 0.25f),
		pBkgImage->GetMemDC(),
		int(0),
		int(0),
		int(pBkgImage->GetSegmentationScale().x),
		int(pBkgImage->GetSegmentationScale().y),
		RGB(255, 0, 255));

	TransparentBlt(_hdc,
		int(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
		int(pOwner->GetPosition().y + (pOwner->GetScale().y * 0.25f)),
		int(pOwner->GetScale().x),
		int(pOwner->GetScale().y * 0.25f),
		pBkgImage->GetMemDC(),
		int(0),
		int(0),
		int(pBkgImage->GetSegmentationScale().x),
		int(pBkgImage->GetSegmentationScale().y),
		RGB(255, 0, 255));

	// ** Box
	Transform boxTransInfo = pOwner->GetTransInfo();
	boxTransInfo.Scale = boxTransInfo.Scale + 1.0f;
	RenderManager::DrawRect(_hdc, boxTransInfo, RGB(128, 65, 217));

	// ** Player Image
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