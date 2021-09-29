#include "ObjectManager.h"
#include "MathManager.h"
#include "CollisionManager.h"
#include "ObjectFactory.h"
#include "Prototype.h"
#include "Enemy.h"
#include "Bullet.h"

ObjectManager* ObjectManager::Instance = nullptr;

void ObjectManager::Initialize()
{
	PrototypeObject = new Prototype;
	PrototypeObject->CreatePrototype();
}

void ObjectManager::Update()
{
	// ** 모든 활성화 오브젝트 간 충돌 검사
	CheckCollision();

	// ** 모든 오브젝트의 Status를 체크하여 Update 또는 Recall 처리
	auto enableList = ObjectManager::GetInstance()->GetEnableObjectList();
	for ( auto ListIter1 = enableList->begin(); ListIter1 != enableList->end(); ++ListIter1 )
	{
		for ( auto ObjIter1 = ListIter1->second.begin(); ObjIter1 != ListIter1->second.end(); )
		{
			// ** Status를 체크하여 Update 또는 Recall 해준다
			switch ( (*ObjIter1)->GetStatus() )
			{
				case eObjectStatus::DESTROYED:
					RecallObject(*ObjIter1++);
					break;
				case eObjectStatus::ACTIVATED:
					(*ObjIter1)->Update(); // ** Update
					[[fallthrough]];
				default:
					++ObjIter1;
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

Object* ObjectManager::CreateObject(eObjectKey _Key)
{
	// ** 새로운 객체를 생성해주어야 한다. 생성은 원형 객체를 복사생성하는 방식으로 생성할 것이다.
	// ** 그러려면 먼저 원형객체가 존재하는지 찾는다.
	Object* pProtoObject = PrototypeObject->FindPrototypeObject(_Key);

	// ** 원형객체가 없다면....
	if ( pProtoObject == nullptr )
		return nullptr;

	// ** 원형 객체를 찾았다면 원형객체를 복사 생성한다.
	Object* pObject = pProtoObject->Clone();
	pObject->Initialize();

	return pObject;
}

Object* ObjectManager::CreateObject(eObjectKey _Key, Vector3 _Position)
{
	// ** 새로운 객체를 생성해주어야 한다. 생성은 원형 객체를 복사생성하는 방식으로 생성할 것이다.
	// ** 그러려면 먼저 원형객체가 존재하는지 찾는다.
	Object* pProtoObject = PrototypeObject->FindPrototypeObject(_Key);

	// ** 원형객체가 없다면....
	if ( pProtoObject == nullptr )
		return nullptr;
		
	// ** 원형 객체를 찾았다면 원형객체를 복사 생성한다.
	Object* pObject = pProtoObject->Clone();
	pObject->Initialize();
	pObject->SetPosition(_Position);

	return pObject;
}

Bridge* ObjectManager::CreateBridge(eBridgeKey _Key)
{
	// ** 새로운 객체를 생성해주어야 한다. 생성은 원형 객체를 복사생성하는 방식으로 생성할 것이다.
	// ** 그러려면 먼저 원형객체가 존재하는지 찾는다.
	Bridge* pProtoBridge = PrototypeObject->FindPrototypeBridge(_Key);

	// ** 원형객체가 없다면....
	if ( pProtoBridge == nullptr )
		return nullptr;
	
	// ** 원형 객체를 찾았다면 원형객체를 복사 생성한다.
	Bridge* pBridge = pProtoBridge->Clone();
	pBridge->Initialize();

	return pBridge;
}

void ObjectManager::AddObject(map<eObjectKey, list<Object*>>& _TargetList, Object* _pObject)
{
	// ** 키값으로 탐색후 탐색이 완료된 결과물을 반환.
	map<eObjectKey, list<Object*>>::iterator ListIter = _TargetList.find(_pObject->GetKey());

	// ** 만약 결과물이 존재하지 않는다면....
	if ( ListIter == _TargetList.end() )
	{
		// ** 새로운 리스트를 생성.
		list<Object*> TempList;

		TempList.push_back(_pObject);

		// ** 오브젝트가 추가된 리스트를 맵에 삽입.
		_TargetList.insert(make_pair(_pObject->GetKey(), TempList));
	}
	// ** 결과물이 존재 한다면...
	else
	{
		// ** 해당 리스트에 오브젝트를 추가
		ListIter->second.push_back(_pObject);
	}
}

void ObjectManager::AddBridge(map<eBridgeKey, list<Bridge*>>& _TargetList, Bridge* _pBridge)
{
	// ** 키값으로 탐색후 탐색이 완료된 결과물을 반환.
	map<eBridgeKey, list<Bridge*>>::iterator ListIter = _TargetList.find(_pBridge->GetKey());

	// ** 만약 결과물이 존재하지 않는다면....
	if ( ListIter == _TargetList.end() )
	{
		// ** 새로운 리스트를 생성.
		list<Bridge*> TempList;

		TempList.push_back(_pBridge);

		// ** 오브젝트가 추가된 리스트를 맵에 삽입.
		_TargetList.insert(make_pair(_pBridge->GetKey(), TempList));
	}
	// ** 결과물이 존재 한다면...
	else
	{
		// ** 해당 리스트에 오브젝트를 추가
		ListIter->second.push_back(_pBridge);
	}
}

void ObjectManager::CheckCollision()
{
	auto EnableList = ObjectManager::GetInstance()->GetEnableObjectList();
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

// ** 컨테이너에서 객체를 찾아서 반환. 없다면 Prototype 생성 후 반환
Object* ObjectManager::TakeObject(eObjectKey _Key)
{
	Object* pObject = nullptr;

	// ** DisableList에 생성하려는 오브젝트가 있는지 확인.
	map<eObjectKey, list<Object*>>::iterator iter = DisableObjectList.find(_Key);

	// ** 없으면..
	if ( iter == DisableObjectList.end() || iter->second.empty() )
	{
		// ** Object를 새로 생성하여 EnableList에 추가
		pObject = CreateObject(_Key);
		if ( pObject != nullptr )
		{
			AddObject(EnableObjectList, pObject);
		}
	}
	// ** 있으면..
	else
	{
		// ** DisableList의 앞 Object를 추출.
		pObject = iter->second.front();
		pObject->Initialize();		

		// ** 추출한 Object를 EnableList에 추가 후 DisableList에서 삭제
		AddObject(EnableObjectList, pObject);
		iter->second.pop_front();
	}

	return pObject;
}

// ** 컨테이너에서 객체를 찾아서 반환. 없다면 Prototype 생성 후 반환
Object* ObjectManager::TakeObject(eObjectKey _Key, Vector3 _Position)
{
	Object* pObject = nullptr;

	// ** DisableList에 생성하려는 오브젝트가 있는지 확인.
	map<eObjectKey, list<Object*>>::iterator iter = DisableObjectList.find(_Key);

	// ** 없으면.....
	if (iter == DisableObjectList.end() || iter->second.empty())
	{
		// ** Object를 새로 생성하여 EnableList에 추가
		pObject = CreateObject(_Key, _Position);
		if ( pObject != nullptr )
		{
			AddObject(EnableObjectList, pObject);
		}
	}
	// ** 있으면..
	else
	{
		// ** DisableList의 앞 Object를 추출.
		pObject = iter->second.front();
		pObject->Initialize();
		pObject->SetPosition(_Position);

		// ** 추출한 Object를 EnableList에 추가 후 DisableList에서 삭제
		AddObject(EnableObjectList, pObject);
		iter->second.pop_front();
	}

	return pObject;
}

Bridge* ObjectManager::TakeBridge(eBridgeKey _Key)
{
	Bridge* pBridge = nullptr;

	// ** DisableList에 생성하려는 오브젝트가 있는지 확인.
	map<eBridgeKey, list<Bridge*>>::iterator iter = DisableBridgeList.find(_Key);

	// ** 없으면..
	if ( iter == DisableBridgeList.end() || iter->second.empty() )
	{
		// ** Bridge를 새로 생성하여 EnableList에 추가
		pBridge = CreateBridge(_Key);
		if ( pBridge != nullptr )
		{
			AddBridge(EnableBridgeList, pBridge);
		}
	}
	// ** 있으면..
	else
	{
		// ** DisableList의 앞 Bridge를 추출.
		pBridge = iter->second.front();
		pBridge->Initialize();

		// ** 추출한 Bridge를 EnableList에 추가 후 DisableList에서 삭제
		AddBridge(EnableBridgeList, pBridge);
		iter->second.pop_front();
	}

	return pBridge;
}

void ObjectManager::RecallObject(Object* _pObject)
{
	// ** 해당 Object Release
	_pObject->Release();
	
	// ** 키값으로 Enable ObjectList를 탐색하여 리스트 내 해당 Object 공간 삭제.
	list<Object*>& ObjectList = EnableObjectList.find(_pObject->GetKey())->second;
	ObjectList.erase(find(ObjectList.begin(), ObjectList.end(), _pObject));
	
	// ** 해당 Object를 DisableList에 추가.
	AddObject(DisableObjectList, _pObject);	
}

void ObjectManager::RecallBridge(Bridge* _pBridge)
{
	// ** 해당 Bridge Release
	_pBridge->Release();

	// ** 키값으로 Enable BridgeList를 탐색하여 리스트 내 해당 Bridge 공간 삭제.
	list<Bridge*>& BridgeList = EnableBridgeList.find(_pBridge->GetKey())->second;
	BridgeList.erase(find(BridgeList.begin(), BridgeList.end(), _pBridge));

	// ** 해당 Bridge를 DisableList에 추가.
	AddBridge(DisableBridgeList, _pBridge);
}

list<Object*> ObjectManager::GetObjectList(eObjectKey _ObjectKey)
{
	list<Object*> ResultList;

	auto FindIter = EnableObjectList.find(_ObjectKey);
	if ( FindIter != EnableObjectList.end() )
		ResultList = FindIter->second;

	return ResultList;
}

list<Bridge*> ObjectManager::GetBridgeList(eBridgeKey _BridgeKey)
{
	list<Bridge*> ResultList;

	auto FindIter = EnableBridgeList.find(_BridgeKey);
	if ( FindIter != EnableBridgeList.end() )
		ResultList = FindIter->second;

	return ResultList;
}

void ObjectManager::Release()
{
	// ** 안전한 삭제.
	::Safe_Delete(pPlayer);

	// ** Delete Object
	for (map<eObjectKey, list<Object*>>::iterator iter = DisableObjectList.begin();
		iter != DisableObjectList.end(); ++iter)
	{
		for (list<Object*>::iterator iter2 = iter->second.begin();
			iter2 != iter->second.end(); ++iter2)
		{
			::Safe_Delete((*iter2));
		}
		iter->second.clear();
	}
	DisableObjectList.clear();

	for ( map<eObjectKey, list<Object*>>::iterator iter = EnableObjectList.begin();
		iter != EnableObjectList.end(); ++iter )
	{
		for ( list<Object*>::iterator iter2 = iter->second.begin();
			iter2 != iter->second.end(); ++iter2 )
		{
			::Safe_Delete((*iter2));
		}
	}
	EnableObjectList.clear();

	// ** Delete Bridge
	for ( map<eBridgeKey, list<Bridge*>>::iterator iter = DisableBridgeList.begin();
		iter != DisableBridgeList.end(); ++iter )
	{
		for ( list<Bridge*>::iterator iter2 = iter->second.begin();
			iter2 != iter->second.end(); ++iter2 )
		{
			::Safe_Delete((*iter2));
		}
		iter->second.clear();
	}
	DisableBridgeList.clear();

	for ( map<eBridgeKey, list<Bridge*>>::iterator iter = EnableBridgeList.begin();
		iter != EnableBridgeList.end(); ++iter )
	{
		for ( list<Bridge*>::iterator iter2 = iter->second.begin();
			iter2 != iter->second.end(); ++iter2 )
		{
			::Safe_Delete((*iter2));
		}
	}
	EnableBridgeList.clear();
}
