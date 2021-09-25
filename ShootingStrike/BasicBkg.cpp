#include "BasicBkg.h"
#include "BitmapManager.h"

BasicBkg::BasicBkg()
{
}

BasicBkg::~BasicBkg()
{
	Release();
}

void BasicBkg::Initialize()
{
}

void BasicBkg::Update()
{

}

void BasicBkg::Render(HDC _hdc)
{
	Bitmap* pImage = pOwner->GetImage();
	if ( !pImage )
		return;

	TransparentBlt(_hdc,
		(int)pOwner->GetPosition().x,
		(int)pOwner->GetPosition().y,
		(int)pOwner->GetScale().x,
		(int)pOwner->GetScale().y,
		pOwner->GetImage()->GetMemDC(),
		0,
		0,
		(int)pOwner->GetScale().x,
		(int)pOwner->GetScale().y,
		RGB(255, 0, 255));
}

void BasicBkg::Release()
{

}
