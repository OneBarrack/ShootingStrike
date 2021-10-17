#include "ButtonUI.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "InputManager.h"

ButtonUI::ButtonUI()
	: bExistHoverImage(false)
	, bExistPressedImage(false)
	, buttonState(eButtonState::NORMAL)
	, bOnClick(false)
	, buttonTypeIndex(0)
{

}

ButtonUI::~ButtonUI()
{

}


void ButtonUI::Initialize()
{
	Super::Initialize();

	key = eBridgeKey::UI_BUTTON;
	
	buttonState = eButtonState::NORMAL;
	bExistPressedImage = false;
	bOnClick = false;
	buttonTypeIndex = 0;
}

void ButtonUI::Update()
{
	Super::Update();

	Vector3 mousePos = InputManager::GetInstance()->GetMousePosition();

	// ** 마우스가 버튼 이미지 위에 위치 하는지
	if ( CollisionManager::IsPointInRect(pOwner->GetColliderL(), mousePos))
	{
		// ** 누르는 중
		if ( CHECK_KEYINPUT_STATE(eInputKey::KEY_LBUTTON, eKeyInputState::PRESSED) )
		{
			buttonState = eButtonState::PRESSED;
		}
		// ** 눌렀다 뗀 시점(클릭 완료된 시점)
		else if ( CHECK_KEYINPUT_STATE(eInputKey::KEY_LBUTTON, eKeyInputState::UP) )
		{
			buttonState = eButtonState::NORMAL;
			bOnClick = true;
		}
		// ** 마우스가 버튼 이미지 위에 있음 (누르지 않는 상태)
		else
		{
			buttonState = eButtonState::HOVER;
		}
	}
	else
	{
		buttonState = eButtonState::NORMAL;
	}
}

void ButtonUI::Render(HDC _hdc)
{
	Super::Render(_hdc);

	if ( !pImage )
		return;

	TransparentBlt(_hdc, // ** 최종 출력 위치
		int(pOwner->GetPosition().x - (pOwner->GetScale().x * 0.5f)),
		int(pOwner->GetPosition().y - (pOwner->GetScale().y * 0.5f)),
		int(pOwner->GetScale().x),
		int(pOwner->GetScale().y),
		pImage->GetMemDC(),
		int(pImage->GetSegmentationScale().x * static_cast<int>(buttonState)),
		int(pImage->GetSegmentationScale().y * buttonTypeIndex),
		int(pImage->GetSegmentationScale().x),
		int(pImage->GetSegmentationScale().y),
		RGB(255, 0, 255));
}

void ButtonUI::Release()
{
	Super::Release();
}
