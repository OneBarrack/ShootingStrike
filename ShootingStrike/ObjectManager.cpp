#include "ObjectManager.h"
#include "MathManager.h"
#include "CollisionManager.h"
#include "ObjectFactory.h"
#include "Prototype.h"
#include "Enemy.h"
#include "Bullet.h"

ObjectManager* ObjectManager::pInstance = nullptr;

void ObjectManager::Initialize()
{
	Release();
	
	pPrototypeObject = new Prototype;
	pPrototypeObject->CreatePrototype();
	pPlayer = nullptr;
}

void ObjectManager::Update()
{
	// ** 모든 활성화 오브젝트 간 충돌 검사
	CheckCollision();

	// ** 모든 오브젝트의 Status를 체크하여 Update 또는 Recall 처리
	auto enableList = ObjectManager::GetInstance()->GetEnableObjectList();
	for ( auto listIter = enableList->begin(); listIter != enableList->end(); ++listIter )
	{
		for ( auto objIter = listIter->second.begin(); objIter != listIter->second.end(); )
		{
			// ** Status를 체크하여 Update 또는 Recall 해준다
			switch ( (*objIter)->GetStatus() )
			{
				case eObjectStatus::DESTROYED:
					RecallObject(*objIter++);
					break;
				case eObjectStatus::ACTIVATED:
					(*objIter)->Update(); // ** Update
					[[fallthrough]];
				default:
					++objIter;
					break;
			}
		}
	}
}

void ObjectManager::Render(HDC _hdc)
{
	// ** 모든 Object Rendering
	// ** Buffer MemDC에 모두 그린 후 memDC를 hdc와 스왑시켜 그린다
	map<eObjectKey, list<Object*>>* enableList = ObjectManager::GetInstance()->GetEnableObjectList();
	for ( map<eObjectKey, list<Object*>>::iterator listIter = enableList->begin();
		listIter != enableList->end(); ++listIter )
	{
		for ( list<Object*>::iterator objIter = listIter->second.begin();
			objIter != listIter->second.end(); ++objIter )
		{
			if ( (*objIter)->GetStatus() == eObjectStatus::ACTIVATED )
			{
				(*objIter)->Render(_hdc);
			}
		}
	}
}

Object* ObjectManager::CreateObject(eObjectKey _key)
{
	// ** 새로운 객체를 생성해주어야 한다. 생성은 원형 객체를 복사생성하는 방식으로 생성할 것이다.
	// ** 그러려면 먼저 원형객체가 존재하는지 찾는다.
	Object* pProtoObject = pPrototypeObject->FindPrototypeObject(_key);

	// ** 원형객체가 없다면....
	if ( pProtoObject == nullptr )
		return nullptr;

	// ** 원형 객체를 찾았다면 원형객체를 복사 생성한다.
	Object* pObject = pProtoObject->Clone();
	pObject->Initialize();

	return pObject;
}

Object* ObjectManager::CreateObject(eObjectKey _key, Vector3 _position)
{
	// ** 새로운 객체를 생성해주어야 한다. 생성은 원형 객체를 복사생성하는 방식으로 생성할 것이다.
	// ** 그러려면 먼저 원형객체가 존재하는지 찾는다.
	Object* pProtoObject = pPrototypeObject->FindPrototypeObject(_key);

	// ** 원형객체가 없다면....
	if ( pProtoObject == nullptr )
		return nullptr;
		
	// ** 원형 객체를 찾았다면 원형객체를 복사 생성한다.
	Object* pObject = pProtoObject->Clone();
	pObject->Initialize();
	pObject->SetPosition(_position);

	return pObject;
}

Bridge* ObjectManager::CreateBridge(eBridgeKey _key)
{
	// ** 새로운 객체를 생성해주어야 한다. 생성은 원형 객체를 복사생성하는 방식으로 생성할 것이다.
	// ** 그러려면 먼저 원형객체가 존재하는지 찾는다.
	Bridge* pProtoBridge = pPrototypeObject->FindPrototypeBridge(_key);

	// ** 원형객체가 없다면....
	if ( pProtoBridge == nullptr )
		return nullptr;
	
	// ** 원형 객체를 찾았다면 원형객체를 복사 생성한다.
	Bridge* pBridge = pProtoBridge->Clone();
	pBridge->Initialize();

	return pBridge;
}

void ObjectManager::AddObject(map<eObjectKey, list<Object*>>& _targetList, Object* _pObject)
{
	// ** 키값으로 탐색후 탐색이 완료된 결과물을 반환.
	map<eObjectKey, list<Object*>>::iterator listIter = _targetList.find(_pObject->GetKey());

	// ** 만약 결과물이 존재하지 않는다면....
	if ( listIter == _targetList.end() )
	{
		// ** 새로운 리스트를 생성.
		list<Object*> tempList;

		tempList.push_back(_pObject);

		// ** 오브젝트가 추가된 리스트를 맵에 삽입.
		_targetList.insert(make_pair(_pObject->GetKey(), tempList));
	}
	// ** 결과물이 존재 한다면...
	else
	{
		// ** 해당 리스트에 오브젝트를 추가
		listIter->second.push_back(_pObject);
	}
}

void ObjectManager::AddBridge(map<eBridgeKey, list<Bridge*>>& _targetList, Bridge* _pBridge)
{
	// ** 키값으로 탐색후 탐색이 완료된 결과물을 반환.
	map<eBridgeKey, list<Bridge*>>::iterator listIter = _targetList.find(_pBridge->GetKey());

	// ** 만약 결과물이 존재하지 않는다면....
	if ( listIter == _targetList.end() )
	{
		// ** 새로운 리스트를 생성.
		list<Bridge*> tempList;

		tempList.push_back(_pBridge);

		// ** 오브젝트가 추가된 리스트를 맵에 삽입.
		_targetList.insert(make_pair(_pBridge->GetKey(), tempList));
	}
	// ** 결과물이 존재 한다면...
	else
	{
		// ** 해당 리스트에 오브젝트를 추가
		listIter->second.push_back(_pBridge);
	}
}

void ObjectManager::CheckCollision()
{
	/** 캐릭터와 총알, 아이템간 충돌체크 **/
	// Bullet - Character 충돌체크
	list<Object*> enableBulletList = enableObjectList[eObjectKey::BULLET];
	for ( auto bulltetIter = enableBulletList.begin(); bulltetIter != enableBulletList.end(); ++bulltetIter )
	{
		Object* pBulletObject = *bulltetIter;
		if ( pBulletObject->IsGeneratedCollisionEvent() == false )
			continue;

		switch ( static_cast<Bullet*>(pBulletObject)->GetOwner()->GetKey() )
		{
			case eObjectKey::PLAYER:
			{
				list<Object*> enableEnemyList = enableObjectList[eObjectKey::ENEMY];
				for ( auto EnemyIter = enableEnemyList.begin(); EnemyIter != enableEnemyList.end(); ++EnemyIter )
				{
					Object* pEnemyObject = *EnemyIter;
					if ( CollisionManager::IsCollision(pEnemyObject, pBulletObject) )
					{
						// 충돌 트리거 발동
						pEnemyObject->OnCollision(pBulletObject);
						pBulletObject->OnCollision(pEnemyObject);
					}
				}				
				break;
			}
			case eObjectKey::ENEMY:
			{
				if ( CollisionManager::IsCollision(pPlayer, pBulletObject) )
				{
					// 충돌 트리거 발동
					pPlayer->OnCollision(pBulletObject);
					pBulletObject->OnCollision(pPlayer);
				}
				break;
			}
		}	
	}

	// Item - Character 충돌체크
	list<Object*> enableItemList = enableObjectList[eObjectKey::ITEM];
	for ( auto itemIter = enableItemList.begin(); itemIter != enableItemList.end(); ++itemIter )
	{
		Object* pItemObject = *itemIter;
		if ( pItemObject->IsGeneratedCollisionEvent() == false )
			continue;

		list<Object*> enableEnemyList = enableObjectList[eObjectKey::ENEMY];
		for ( auto EnemyIter = enableEnemyList.begin(); EnemyIter != enableEnemyList.end(); ++EnemyIter )
		{
			Object* pEnemyObject = *EnemyIter;
			if ( CollisionManager::IsCollision(pEnemyObject, pItemObject) )
			{
				// 충돌 트리거 발동
				pEnemyObject->OnCollision(pItemObject);
				pItemObject->OnCollision(pEnemyObject);
			}
		}
		if ( CollisionManager::IsCollision(pPlayer, pItemObject) )
		{
			// 충돌 트리거 발동
			pPlayer->OnCollision(pItemObject);
			pItemObject->OnCollision(pPlayer);
		}
	}

	// Character(Player - Enemy) 충돌체크
	list<Object*> enableEnemyList = enableObjectList[eObjectKey::ENEMY];
	for ( auto enemyIter = enableEnemyList.begin(); enemyIter != enableEnemyList.end(); ++enemyIter )
	{
		Object* pEnemyObject = *enemyIter;
		if ( pEnemyObject->IsGeneratedCollisionEvent() == false )
			continue;

		if ( CollisionManager::IsCollision(pPlayer, pEnemyObject) )
		{
			// 충돌 트리거 발동
			pPlayer->OnCollision(pEnemyObject);
			pEnemyObject->OnCollision(pPlayer);
		}
	}
}

// ** 컨테이너에서 객체를 찾아서 반환. 없다면 Prototype 생성 후 반환
Object* ObjectManager::NewObject(eObjectKey _key)
{
	Object* pObject = nullptr;

	// ** DisableList에 생성하려는 오브젝트가 있는지 확인.
	map<eObjectKey, list<Object*>>::iterator iter = disableObjectList.find(_key);

	// ** 없으면..
	if ( iter == disableObjectList.end() || iter->second.empty() )
	{
		// ** Object를 새로 생성하여 EnableList에 추가
		pObject = CreateObject(_key);
		if ( pObject != nullptr )
		{
			AddObject(enableObjectList, pObject);
		}
	}
	// ** 있으면..
	else
	{
		// ** DisableList의 앞 Object를 추출.
		pObject = iter->second.front();
		pObject->Initialize();		

		// ** 추출한 Object를 EnableList에 추가 후 DisableList에서 삭제
		AddObject(enableObjectList, pObject);
		iter->second.pop_front();
	}

	return pObject;
}

// ** 컨테이너에서 객체를 찾아서 반환. 없다면 Prototype 생성 후 반환
Object* ObjectManager::NewObject(eObjectKey _key, Vector3 _position)
{
	Object* pObject = nullptr;

	// ** DisableList에 생성하려는 오브젝트가 있는지 확인.
	map<eObjectKey, list<Object*>>::iterator iter = disableObjectList.find(_key);

	// ** 없으면.....
	if (iter == disableObjectList.end() || iter->second.empty())
	{
		// ** Object를 새로 생성하여 EnableList에 추가
		pObject = CreateObject(_key, _position);
		if ( pObject != nullptr )
		{
			AddObject(enableObjectList, pObject);
		}
	}
	// ** 있으면..
	else
	{
		// ** DisableList의 앞 Object를 추출.
		pObject = iter->second.front();
		pObject->Initialize();
		pObject->SetPosition(_position);

		// ** 추출한 Object를 EnableList에 추가 후 DisableList에서 삭제
		AddObject(enableObjectList, pObject);
		iter->second.pop_front();
	}

	return pObject;
}

Bridge* ObjectManager::NewBridge(eBridgeKey _key)
{
	Bridge* pBridge = nullptr;

	// ** DisableList에 생성하려는 오브젝트가 있는지 확인.
	map<eBridgeKey, list<Bridge*>>::iterator iter = disableBridgeList.find(_key);

	// ** 없으면..
	if ( iter == disableBridgeList.end() || iter->second.empty() )
	{
		// ** Bridge를 새로 생성하여 EnableList에 추가
		pBridge = CreateBridge(_key);
		if ( pBridge != nullptr )
		{
			AddBridge(enableBridgeList, pBridge);
		}
	}
	// ** 있으면..
	else
	{
		// ** DisableList의 앞 Bridge를 추출.
		pBridge = iter->second.front();
		pBridge->Initialize();

		// ** 추출한 Bridge를 EnableList에 추가 후 DisableList에서 삭제
		AddBridge(enableBridgeList, pBridge);
		iter->second.pop_front();
	}

	return pBridge;
}

void ObjectManager::RecallObject(Object* _pObject)
{
	// ** 해당 Object Release
	_pObject->Release();
	
	// ** 키값으로 Enable ObjectList를 탐색하여 리스트 내 해당 Object 공간 삭제.
	list<Object*>& objectList = enableObjectList.find(_pObject->GetKey())->second;
	objectList.erase(find(objectList.begin(), objectList.end(), _pObject));
	
	// ** 해당 Object를 DisableList에 추가.
	AddObject(disableObjectList, _pObject);
}

void ObjectManager::RecallBridge(Bridge* _pBridge)
{
	// ** 해당 Bridge Release
	_pBridge->Release();

	// ** 키값으로 Enable BridgeList를 탐색하여 리스트 내 해당 Bridge 공간 삭제.
	list<Bridge*>& bridgeList = enableBridgeList.find(_pBridge->GetKey())->second;
	bridgeList.erase(find(bridgeList.begin(), bridgeList.end(), _pBridge));

	// ** 해당 Bridge를 DisableList에 추가.
	AddBridge(disableBridgeList, _pBridge);
}

list<Object*> ObjectManager::GetObjectList(eObjectKey _objectKey)
{
	auto FindIter = enableObjectList.find(_objectKey);
	if ( FindIter != enableObjectList.end() )
		return FindIter->second;

	return list<Object*>();
}

list<Bridge*> ObjectManager::GetBridgeList(eBridgeKey _bridgeKey)
{
	auto FindIter = enableBridgeList.find(_bridgeKey);
	if ( FindIter != enableBridgeList.end() )
		return FindIter->second;

	return list<Bridge*>();
}

Object* ObjectManager::FindObjectWithTag(eTagName _tagName)
{
	for ( map<eObjectKey, list<Object*>>::iterator listIter = enableObjectList.begin();
		listIter != enableObjectList.end(); ++listIter )
	{
		for ( list<Object*>::iterator objIter = listIter->second.begin();
			objIter != listIter->second.end(); ++objIter )
		{
			if ( (*objIter)->GetTagName() == _tagName )
				return (*objIter);
		}
	}
	return nullptr;
}

Object* ObjectManager::FindObjectWithTag(eObjectKey _objectKey, eTagName _tagName)
{
	map<eObjectKey, list<Object*>>::iterator findIter = enableObjectList.find(_objectKey);
	if ( findIter != enableObjectList.end() )
	{
		list<Object*> objectList = findIter->second;
		for ( Object* pObject : objectList )
		{
			if ( pObject->GetTagName() == _tagName )
				return pObject;
		}
	}

	return nullptr;
}

void ObjectManager::Release()
{
	// ** Delete PrototypeObject
	Safe_Delete(pPrototypeObject);

	// ** Recall Player
	if ( pPlayer )
		RecallObject(pPlayer);	
	
	/** 
	* Object / Bridge EnableList에 대한 Recall 처리.
	* 
	* 게임이 정상 종료 되었다면 Player Recall을 마지막으로 모든 오브젝트/브릿지는 회수되어 있어야 한다.
	* 즉, EnableList에 데이터가 남아있다면 어디선가 Recall 해주지 않았거나 비정상 종료라는 뜻.
	* 혹여나 일부 Object 또는 Bridge가 회수되지 못했을 시를 대비한 예외처리이다.
	*/

	// ** Recall Enable Object
	for ( map<eObjectKey, list<Object*>>::iterator listIter = enableObjectList.begin();
		listIter != enableObjectList.end(); ++listIter )
	{
		for ( list<Object*>::iterator objIter = listIter->second.begin();
			objIter != listIter->second.end(); )
		{
			RecallObject((*objIter++));
		}
	}
	enableObjectList.clear();
	
	// ** Recall Enable Bridge
	for ( map<eBridgeKey, list<Bridge*>>::iterator listIter = enableBridgeList.begin();
		listIter != enableBridgeList.end(); ++listIter )
	{
		for ( list<Bridge*>::iterator bridgeIter = listIter->second.begin();
			bridgeIter != listIter->second.end(); )
		{
			RecallBridge((*bridgeIter++));
		}
	}
	enableBridgeList.clear();

	// ** Delete Object
	for (map<eObjectKey, list<Object*>>::iterator listIter = disableObjectList.begin();
		listIter != disableObjectList.end(); ++listIter)
	{
		for (list<Object*>::iterator objIter = listIter->second.begin();
			objIter != listIter->second.end(); ++objIter)
		{
			::Safe_Delete((*objIter));
		}
		listIter->second.clear();
	}
	disableObjectList.clear();	

	// ** Delete Bridge		
	for ( map<eBridgeKey, list<Bridge*>>::iterator listIter = disableBridgeList.begin();
		listIter != disableBridgeList.end(); ++listIter )
	{
		for ( list<Bridge*>::iterator bridgeIter = listIter->second.begin();
			bridgeIter != listIter->second.end(); ++bridgeIter )
		{
			::Safe_Delete((*bridgeIter));
		}
		listIter->second.clear();
	}
	disableBridgeList.clear();	
}
