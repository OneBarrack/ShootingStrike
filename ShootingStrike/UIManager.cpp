#include "UIManager.h"
#include "ObjectManager.h"
#include "BitmapManager.h"
#include "Button.h"

Button* UIManager::MakeButton(Transform _TransInfo, Transform _Collider, eImageKey _ImageKey)
{
	Button* pButton = static_cast<Button*>(ObjectManager::GetInstance()->TakeObject(eObjectKey::UI_BUTTON));
	pButton->SetTransInfo(_TransInfo);
	pButton->SetCollider(_Collider);
	pButton->SetImage(BitmapManager::GetInstance()->GetImage(_ImageKey));

	return pButton;
}
