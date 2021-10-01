#include "ButtonUI.h"
#include "InputManager.h"
#include "CollisionManager.h"

ButtonUI::ButtonUI()
	: bExistHoverImage(false)
	, bExistPressedImage(false)
	, buttonState(eButtonState::NORMAL)
	, bOnClick(false)
{

}

ButtonUI::~ButtonUI()
{

}


void ButtonUI::Initialize()
{
	transInfo.Position = Vector3(0.0f, 0.0f);
	transInfo.Scale = Vector3(0.0f, 0.0f);
	transInfo.Direction = Vector3(0.0f, 0.0f);
		
	collider.Position = transInfo.Position;
	collider.Scale = transInfo.Scale;

	key = eObjectKey::UI_BUTTON;
	status = eObjectStatus::ACTIVATED;
	collisionType = eCollisionType::RECT;
	
	bGenerateCollisionEvent = false;
	
	buttonState = eButtonState::NORMAL;
	bOnClick = false;
}

void ButtonUI::Update()
{
	Vector3 mousePos = InputManager::GetInstance()->GetMousePosition();

	// ** 마우스가 버튼 이미지 위에 위치 하는지
	if ( CollisionManager::IsPointInRect(GetColliderL(), mousePos))
	{
		// ** 누르는 중
		if ( CheckKeyInputStatus(eInputKey::KEY_LBUTTON, eKeyInputState::PRESSED) )
		{
			buttonState = eButtonState::PRESSED;
		}
		// ** 눌렀다 뗀 시점(클릭 완료된 시점)
		else if ( CheckKeyInputStatus(eInputKey::KEY_LBUTTON, eKeyInputState::UP) )
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

	// ** 충돌체 갱신
	collider = transInfo;
}

void ButtonUI::Render(HDC _hdc)
{
	if ( !pImage )
		return;

	TransparentBlt(_hdc, // ** 최종 출력 위치
		int(transInfo.Position.x - (transInfo.Scale.x * 0.5f)),
		int(transInfo.Position.y - (transInfo.Scale.y * 0.5f)),
		int(transInfo.Scale.x),
		int(transInfo.Scale.y),
		pImage->GetMemDC(),
		int(transInfo.Scale.x * static_cast<int>(buttonState)),
		0,
		int(transInfo.Scale.x),
		int(transInfo.Scale.y),
		RGB(255, 0, 255));
}

void ButtonUI::Release()
{

}

void ButtonUI::OnCollision(Object* _pObject)
{

}
