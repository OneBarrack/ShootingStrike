#include "WarningEffect.h"
#include "BitmapManager.h"

WarningEffect::WarningEffect()
	: pFadeBackImage(nullptr)
	, alpha(0)
	, fadeSpeed(0)
	, fadeCycleCount(0)
	, maxFadeCycleCount(0)
{

}

WarningEffect::~WarningEffect()
{
}


void WarningEffect::Initialize()
{
	Super::Initialize();

	segmentImageCount = 1;
	key = eBridgeKey::EFFECT_WARNING;

	pFadeBackImage = BitmapManager::GetInstance()->GetImage(eImageKey::FADEBACK_RED);
	pImage = BitmapManager::GetInstance()->GetImage(eImageKey::WARNING);;

	alpha = 0;
	fadeSpeed = 3;
	fadeCycleCount = 0;
	maxFadeCycleCount = 3;
}

void WarningEffect::Update()
{
	Super::Update();

	// ** max fade cycle 횟수에 도달하면 오브젝트 삭제
	if ( fadeCycleCount == maxFadeCycleCount )
		pOwner->SetStatus(eObjectStatus::DESTROYED);

	//ReceiveInfoFromOwner();
	//SendInfoToOwner();
}

void WarningEffect::Render(HDC _hdc)
{
	Super::Render(_hdc);

	if ( !pImage )
		return;
	
	if ( alpha == 0 )
	{		
		fadeSpeed = abs(fadeSpeed);
	}
	if ( alpha == fadeSpeed * 40 )
	{		
		fadeSpeed = -abs(fadeSpeed);
	}

	alpha += fadeSpeed;
	
	// ** alpha가 0이 되면 한 cycle이 끝난 것
	if ( alpha == 0 )
		++fadeCycleCount;

	BLENDFUNCTION bf;
	bf.AlphaFormat = 0;			// ** 일반 비트맵 0, 32비트 비트맵 AC_SRC_ALPHA
	bf.BlendFlags = 0;			// ** 사용되지 않는 옵션. 무조건 0
	bf.BlendOp = AC_SRC_OVER;  // ** AC_SRC_OVER
	bf.SourceConstantAlpha = alpha;		// ** 투명도(투명 0 - 불투명 255)

	// ** Fade Background 이미지를 바탕으로 Fade 효과 부여
	AlphaBlend(_hdc, 0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT,
		pFadeBackImage->GetMemDC(),
		0, 0, WINDOWS_WIDTH, WINDOWS_HEIGHT, bf);
	
	// ** Warning Image
	TransparentBlt(_hdc,
		int(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
		int(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
		int(pOwner->GetScale().x),
		int(pOwner->GetScale().y),
		pImage->GetMemDC(),
		(int)(pImage->GetSegmentationScale().x * pOwner->GetImageOffsetOrder().x),
		(int)(pImage->GetSegmentationScale().y * pOwner->GetImageOffsetOrder().y),
		(int)(pImage->GetSegmentationScale().x),
		(int)(pImage->GetSegmentationScale().y),
		RGB(255, 0, 255));	
}

void WarningEffect::Release()
{
	Super::Release();
}