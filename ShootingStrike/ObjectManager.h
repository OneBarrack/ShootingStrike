#pragma once
#include "Headers.h"

class Object;
class Prototype;
class Bridge;
class ObjectManager
{
private:
	static ObjectManager* pInstance;
public:
	static ObjectManager* GetInstance()
	{
		if (pInstance == nullptr)
			pInstance = new ObjectManager;

		return pInstance;
	}
private:
	// ** Prototype
	Prototype* pPrototypeObject;

	// ** 플레이어
	Object* pPlayer;

	// ** 오브젝트 리스트
	map<eObjectKey, list<Object*>> enableObjectList;
	map<eObjectKey, list<Object*>> disableObjectList;

	// ** 브릿지 리스트
	map<eBridgeKey, list<Bridge*>> enableBridgeList;
	map<eBridgeKey, list<Bridge*>> disableBridgeList;

public:
	// ** 초기화
	void Initialize();	
	void Update();
	void Render(HDC _hdc);
	void Release();

	// ** 플레이어를 반환.
	Object* GetPlayer() { return pPlayer; }
	void SetPlayer(Object* _pPlayer) { pPlayer = _pPlayer; }

	// ** 컨테이너에서 오브젝트 객체를 찾아서 반환. 없다면 Prototype 생성 후 반환
	Object* NewObject(eObjectKey _key);
	Object* NewObject(eObjectKey _key, Vector3 _position);
	
	// ** 컨테이너에서 브릿지 객체를 찾아서 반환. 없다면 Prototype 생성 후 반환
	Bridge* NewBridge(eBridgeKey _key);

	// ** 사용후 더이상 사용하지 않는 오브젝트 회수
	void RecallObject(Object* _pObject);

	// ** 사용후 더이상 사용하지 않는 브릿지 회수
	void RecallBridge(Bridge* _pBridge);

	// ** map 컨테이너를 사용하고있는 Object Enable/Disable List를 반환.
	map<eObjectKey, list<Object*>>* GetEnableObjectList() { return &enableObjectList; }
	map<eObjectKey, list<Object*>>* GetDisableObjectList() { return &disableObjectList; }

	// ** map 컨테이너를 사용하고있는 Bridge Enable/Disable List를 반환.
	map<eBridgeKey, list<Bridge*>>* GetEnableBridgeList() { return &enableBridgeList; }
	map<eBridgeKey, list<Bridge*>>* GetDisableBridgeList() { return &disableBridgeList; }

	// ** ObjectKey에 해당하는 Object List를 반환
	list<Object*> GetObjectList(eObjectKey _objectKey);

	// ** BridgeKey에 해당하는 Bridge List를 반환
	list<Bridge*> GetBridgeList(eBridgeKey _bridgeKey);	

	// ** TagName에 해당하는 Object를 반환
	Object* FindObjectWithTag(eTagName _tagName);
	Object* FindObjectWithTag(eObjectKey _objectKey, eTagName _tagName);

private:
	// ** 오브젝트 객체 생성
	Object* CreateObject(eObjectKey _key);
	Object* CreateObject(eObjectKey _key, Vector3 _position);

	// ** 브릿지 객체 생성
	Bridge* CreateBridge(eBridgeKey _key);

	// ** 오브젝트 객체 추가
	void AddObject(map<eObjectKey, list<Object*>>& _targetList, Object* _pObject);

	// ** 브릿지 객체 추가
	void AddBridge(map<eBridgeKey, list<Bridge*>>& _targetList, Bridge* _pObject);

	// ** 모든 활성화 오브젝트 간 충돌 검사
	void CheckCollision();

private:
	ObjectManager() : pPrototypeObject(nullptr), pPlayer(nullptr) { }
public:
	~ObjectManager() { Release(); }
};

