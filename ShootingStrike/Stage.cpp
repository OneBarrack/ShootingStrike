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

	/*
	// ** 오브젝트 매니저에서 총알 리스트를 받아옴. (포인터로...)
	BulletList = ObjectManager::GetInstance()->GetBulletList();

	// ** 오브젝트 매니저에서 몬스터 리스트를 받아옴. (포인터로...)
	EnemyList = ObjectManager::GetInstance()->GetEnemyList();
	*/

	Bridge* pBridge = new StageBackground;
	pBackground = ObjectManager::GetInstance()->TakeObject(eObjectKey::BACKGROUND, pBridge);

	static_cast<Player*>(pPlayer)->SetStatus(eObjectStatus::ACTIVATED);
	static_cast<Player*>(pPlayer)->SpawnPlayer();	
}

void Stage::Update()
{
	// ** 모든 활성화 오브젝트 간 충돌 검사
	CheckCollisionForAllObjects();
	UpdateForAllObjects();
}

void Stage::Render(HDC _hdc)
{
	RenderForAllObjects(_hdc);
}

void Stage::Release()
{
	if ( pBackground )
	{
		pBackground->Release();
		ObjectManager::GetInstance()->RecallObject(pBackground);	
	}
}

void Stage::CheckCollisionForAllObjects()
{
	auto EnableList = ObjectManager::GetInstance()->GetEnableList();
	for ( auto ListIter1 = EnableList->begin(); ListIter1 != EnableList->end(); ++ListIter1 )
	{
		for ( auto ObjIter1 = ListIter1->second.begin(); ObjIter1 != ListIter1->second.end(); ++ObjIter1 )
		{
			if ( (*ObjIter1)->IsGeneratedCollisionEvent() == false )
				continue;

			// ** 전체 Object간 충돌체크
			auto ListIter2 = ListIter1;
			for ( ++ListIter2; ListIter2 != EnableList->end(); ++ListIter2 )
			{
				for ( auto ObjIter2 = ListIter2->second.begin(); ObjIter2 != ListIter2->second.end(); ++ObjIter2 )
				{
					if ( (*ObjIter2)->IsGeneratedCollisionEvent() == false )
						continue;

					if ( CollisionManager::IsCollision(*ObjIter1, *ObjIter2) )
					{
						// 충돌 트리거 발동
						(*ObjIter1)->OnCollision(*ObjIter2);
						(*ObjIter2)->OnCollision(*ObjIter1);
					}
				}
			}
		}
	}
}

void Stage::CheckPositionInsideStage(Object* _pObject)
{
	// ** Object의 Position과 Stage의 바운더리를 받아온다
	Vector3 ObjectPosition = _pObject->GetPosition();
	RectF ScreenRect(
		pBackground->GetPosition().x - (pBackground->GetScale().x * 0.5f),
		pBackground->GetPosition().y - (pBackground->GetScale().y * 0.5f),
		pBackground->GetPosition().x + (pBackground->GetScale().x * 0.5f),
		pBackground->GetPosition().y + (pBackground->GetScale().y * 0.5f));	

	float Offset = 0.0f;
	switch ( _pObject->GetKey() )
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
			_pObject->SetPosition(ObjectPosition);
			break;			
		case eObjectKey::ENEMY:
			[[fallthrough]];
		case eObjectKey::BULLET:
			// ** Stage 바운더리를 넓힐 여유분 길이의 Offset
			Offset = 0.0f;

			// ** Stage 바운더리를 Offset 만큼 넓힌다
			ScreenRect.Left   -= Offset;
			ScreenRect.Top    -= Offset;
			ScreenRect.Right  += Offset;
			ScreenRect.Bottom += Offset;

			// ** Stage의 바운더리 내 Object Position이 위치하지 않으면 Destroy
			if ( !CollisionManager::IsPointInRect(ScreenRect, ObjectPosition) )
				_pObject->SetStatus(eObjectStatus::DESTROYED);
			break;
		default:
			break;
	}	
}

void Stage::UpdateForAllObjects()
{
	auto enableList = ObjectManager::GetInstance()->GetEnableList();
	for ( auto ListIter1 = enableList->begin(); ListIter1 != enableList->end(); ++ListIter1 )
	{
		for ( auto ObjIter1 = ListIter1->second.begin(); ObjIter1 != ListIter1->second.end(); )
		{
			// ** Status를 체크하여 Update 또는 Recall 해준다
			switch ( (*ObjIter1)->GetStatus() )
			{
				case eObjectStatus::DESTROYED:
					ObjectManager::GetInstance()->RecallObject(*ObjIter1++);
					break;
				case eObjectStatus::ACTIVATED:					
					(*ObjIter1)->Update(); // ** Update			
					CheckPositionInsideStage(*ObjIter1); // ** 오브젝트가 Stage 내부를 벗어났는지 체크
					[[fallthrough]];
				default:
					++ObjIter1;
					break;
			}
		}
	}

	#ifdef GAME_DEBUG_MODE
	static ULONGLONG Time = GetTickCount64();
	if ( Time + 1000 < GetTickCount64() )
	{
		auto temp = ObjectManager::GetInstance()->GetEnableList();
		auto temp2 = temp->find(eObjectKey::BULLET);
		if ( temp2 != temp->end() )
		{
			cout << temp2->second.size() << endl;
		}
		Time = GetTickCount64();
	}
	#endif // GAME_DEBUG_MODE
}

void Stage::RenderForAllObjects(HDC _hdc)
{
	// ** Buffer MemDC에 모두 그린 후 memDC를 hdc와 스왑시켜 그린다
	map<eObjectKey, list<Object*>>* enableList = ObjectManager::GetInstance()->GetEnableList();
	for ( map<eObjectKey, list<Object*>>::iterator iter = enableList->begin();
		iter != enableList->end(); ++iter )
	{
		for ( list<Object*>::iterator iter2 = iter->second.begin();
			iter2 != iter->second.end(); ++iter2 )
		{
			if ( (*iter2)->GetStatus() == eObjectStatus::ACTIVATED )
			{
				(*iter2)->Render(_hdc);
			}
		}
	}
}
