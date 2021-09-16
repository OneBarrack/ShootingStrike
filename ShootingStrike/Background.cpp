#include "Background.h"
#include "BitmapManager.h"

Background::Background()
{

}

Background::~Background()
{

}


void Background::Initialize()
{
	TransInfo.Position = Vector3(0.0f, 0.0f);
	TransInfo.Direction = Vector3(0.0f, 0.0f);
	TransInfo.Scale = Vector3(1440.0f, 720.0f);

	Key = eObjectKey::BACKGROUND;
	Status = eObjectStatus::ACTIVATED;
	CollisionType = eCollisionType::NONE;

	Offset = 0.0f;
	bAttached = false;
}

int Background::Update()
{
	// ** Image를 한 번에 그릴 경우
	if ( !bAttached )
	{
		// ** 화면의 끝과 Image의 끝이 만나는지 체크, 아직 만나지 않았다면 Offset 증가
		if ( WindowsWidth + Offset < TransInfo.Scale.x )
		{
			++Offset;
		}
		// ** 화면의 끝과 Image의 끝이 만났다면
		else
		{			
			// ** Offset을 0으로 만들고 이어 붙이기 위한 bAttached를 true로 세팅
			Offset = 0;
			bAttached = true;
		}
	}
	// ** Image를 끝까지 그려내어 Image를 이어 붙일 경우
	else
	{
		// ** Offset이 WindowsWidth를 넘어서는지 체크, 아직이라면 Offset 증가
		if ( Offset < WindowsWidth )
		{
			++Offset;
		}
		// ** Offset이 WindowsWidth를 넘어섰다면, 이어붙인 image가 화면 전체를 덮은상태
		else
		{
			// ** Offset을 다시 0으로 만들고 이어붙이기를 종료 하고 
			// ** Image를 한 번에 그리기 위해 bAttached를 false로 세팅
			Offset = 0;
			bAttached = false;
		}	
	}

	return 0;
}

void Background::Render(HDC _hdc)
{
	// ** Image를 한 번에 그림
	if ( !bAttached )
	{
		TransparentBlt(_hdc, 
			0,
			0,
			WindowsWidth,
			WindowsHeight,
			BitmapManager::GetInstance()->GetMemDC(eImageKey::BACKGROUND),
			Offset, 0,
			WindowsWidth,
			WindowsHeight,
			RGB(255, 0, 255));
	}
	// ** Image를 끝까지 그려내어 Image를 이어 붙임
	else
	{
		// ** 앞서 그리던 이미지의 뒷부분을 서서히 앞라인으로 당김
		TransparentBlt(_hdc, 
			0,
			0,
			WindowsWidth - Offset,
			WindowsHeight,
			BitmapManager::GetInstance()->GetMemDC(eImageKey::BACKGROUND),
			(int)TransInfo.Scale.x - WindowsWidth + Offset, 0,
			WindowsWidth - Offset,
			WindowsHeight,
			RGB(255, 0, 255));

		// ** 앞 이미지의 뒷부분에 이미지의 첫 스타트부터 이어붙여 이미지가 연속되도록 함
		TransparentBlt(_hdc, 
			WindowsWidth - Offset,
			0,
			Offset,
			WindowsHeight,
			BitmapManager::GetInstance()->GetMemDC(eImageKey::BACKGROUND),
			0, 0,
			Offset,
			WindowsHeight,
			RGB(255, 0, 255));
	}
}

void Background::Release()
{

}

void Background::OnCollision(Object* _pObject)
{
}
