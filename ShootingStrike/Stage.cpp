#include "Stage.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "Player.h"
#include "EnemyHole.h"
#include "HammerEffect.h"
#include "ObjectFactory.h"
#include "CollisionManager.h"
#include "StageBackground.h"
#include "BitmapManager.h"

Stage::Stage() : pPlayer(nullptr)
{

}

Stage::~Stage()
{
	Release();
}

void Stage::Initialize()
{
	pPlayer = ObjectManager::GetInstance()->GetPlayer();

	Bridge* pBridge = new StageBackground;
	pBackground = ObjectManager::GetInstance()->TakeObject(eObjectKey::BACKGROUND, pBridge);

	static_cast<Player*>(pPlayer)->SetStatus(eObjectStatus::ACTIVATED);
	static_cast<Player*>(pPlayer)->SpawnPlayer();	
}

void Stage::Update()
{
	ObjectManager::GetInstance()->Update();

	CheckPositionInBkgBoundary(eObjectKey::PLAYER);
	CheckPositionInBkgBoundary(eObjectKey::ENEMY);
	CheckPositionInBkgBoundary(eObjectKey::BULLET);
}

void Stage::Render(HDC _hdc)
{
	ObjectManager::GetInstance()->Render(_hdc);
}

void Stage::Release()
{
	if ( pBackground )
	{
		pBackground->Release();
		ObjectManager::GetInstance()->RecallObject(pBackground);	
	}
}

void Stage::CheckPositionInBkgBoundary(eObjectKey _ObjectKey)
{
	// ** Key에 해당하는 Object List를 받아옴
	list<Object*> ObjectList = ObjectManager::GetInstance()->GetObjectList(_ObjectKey);

	// ** List를 돌며 Position 체크
	for ( Object* pObject : ObjectList )
	{
		// ** Object의 Position과 Stage의 바운더리를 받아온다
		Vector3 ObjectPosition = pObject->GetPosition();
		RectF ScreenRect(
			pBackground->GetPosition().x - (pBackground->GetScale().x * 0.5f),
			pBackground->GetPosition().y - (pBackground->GetScale().y * 0.5f),
			pBackground->GetPosition().x + (pBackground->GetScale().x * 0.5f),
			pBackground->GetPosition().y + (pBackground->GetScale().y * 0.5f));

		float Offset = 0.0f;
		switch ( pObject->GetKey() )
		{
			case eObjectKey::PLAYER:
				// ** 테두리 경계선 기준에 몸체가 잘리지 않게 하기 위한 Offset 값
				Offset = 22.0f;

				// ** 좌
				if ( ObjectPosition.x < ScreenRect.Left + Offset )
					ObjectPosition.x = ScreenRect.Left + Offset;
				// ** 우
				if ( ObjectPosition.x > ScreenRect.Right - Offset )
					ObjectPosition.x = ScreenRect.Right - Offset;
				// ** 상
				if ( ObjectPosition.y < ScreenRect.Top - Offset )
					ObjectPosition.y = ScreenRect.Top - Offset;
				// ** 하
				if ( ObjectPosition.y > ScreenRect.Bottom - Offset )
					ObjectPosition.y = ScreenRect.Bottom - Offset;

				// ** 계산된 Position을 다시 플레이어에 세팅
				pObject->SetPosition(ObjectPosition);
				break;
			case eObjectKey::ENEMY:
				[[fallthrough]];
			case eObjectKey::BULLET:
				// ** Stage 바운더리를 넓힐 여유분 길이의 Offset
				Offset = 0.0f;

				// ** Stage 바운더리를 Offset 만큼 넓힌다
				ScreenRect.Left -= Offset;
				ScreenRect.Top -= Offset;
				ScreenRect.Right += Offset;
				ScreenRect.Bottom += Offset;

				// ** Stage의 바운더리 내 Object Position이 위치하지 않으면 Destroy
				if ( !CollisionManager::IsPointInRect(ScreenRect, ObjectPosition) )
					pObject->SetStatus(eObjectStatus::DESTROYED);
				break;
			default:
				break;
		}
	}
}