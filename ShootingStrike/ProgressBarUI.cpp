#include "ProgressBarUI.h"
#include "BitmapManager.h"

ProgressBarUI::ProgressBarUI()
	: pProgressBarImage(nullptr)
	, value(0)
	, maxValue(0)
	, valueRatio(0.0f)
{

}

ProgressBarUI::~ProgressBarUI()
{
}


void ProgressBarUI::Initialize()
{
	Super::Initialize();

	pProgressBarImage = BitmapManager::GetInstance()->GetImage(eImageKey::PROGRESSBAR);
	value = 0;
	maxValue = 0;
	valueRatio = 0.0f;
	key = eBridgeKey::UI_PROGRESSBAR;
}

void ProgressBarUI::Update()
{
	Super::Update();
	
	if ( maxValue > 0 )
		valueRatio = value / (float)maxValue;
}

void ProgressBarUI::Render(HDC _hdc)
{
	Super::Render(_hdc);

	if ( !pProgressBarImage )
		return;

	// ** 최대체력 대비 현재 체력 비율로 x Offset을 조절한다.
	 
	// ** Value
	TransparentBlt(_hdc,
		int(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f * 0.92f)),
		int(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f * 0.67f)),
		int(pOwner->GetScale().x * 0.92f * valueRatio),
		int(pOwner->GetScale().y * 0.7f),
		pProgressBarImage->GetMemDC(),
		int(0),
		int(pProgressBarImage->GetSegmentationScale().y),
		int(pProgressBarImage->GetSegmentationScale().x * valueRatio),
		int(pProgressBarImage->GetSegmentationScale().y),
		RGB(255, 0, 255));

	// ** Box
	TransparentBlt(_hdc,
		int(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
		int(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
		int(pOwner->GetScale().x),
		int(pOwner->GetScale().y),
		pProgressBarImage->GetMemDC(),
		int(0),
		int(0),
		int(pProgressBarImage->GetSegmentationScale().x),
		int(pProgressBarImage->GetSegmentationScale().y),
		RGB(255, 0, 255));
}

void ProgressBarUI::Release()
{
	Super::Release();

	pProgressBarImage = nullptr;
}

void ProgressBarUI::SetValue(int _value, int _maxValue)
{
	value = _value;
	maxValue = _maxValue;
}