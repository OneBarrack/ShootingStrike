#pragma once
#include "Headers.h"

class Object;
class Prototype;
class Bridge;
class ObjectManager
{
private:
	static ObjectManager* Instance;
public:
	static ObjectManager* GetInstance()
	{
		if (Instance == nullptr)
			Instance = new ObjectManager;

		return Instance;
	}
private:
	// ** Prototype
	Prototype* PrototypeObject;

	// ** 플레이어
	Object* pPlayer;

	// ** 오브젝트 리스트
	map<eObjectKey, list<Object*>> EnableObjectList;
	map<eObjectKey, list<Object*>> DisableObjectList;

	// ** 브릿지 리스트
	map<eBridgeKey, list<Bridge*>> EnableBridgeList;
	map<eBridgeKey, list<Bridge*>> DisableBridgeList;

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
	Object* TakeObject(eObjectKey _Key);
	Object* TakeObject(eObjectKey _Key, Vector3 _Position);
	
	// ** 컨테이너에서 브릿지 객체를 찾아서 반환. 없다면 Prototype 생성 후 반환
	Bridge* TakeBridge(eBridgeKey _Key);

	// ** 사용후 더이상 사용하지 않는 오브젝트 회수
	void RecallObject(Object* _pObject);

	// ** 사용후 더이상 사용하지 않는 브릿지 회수
	void RecallBridge(Bridge* _pBridge);

	// ** map 컨테이너를 사용하고있는 Object Enable/Disable List를 반환.
	map<eObjectKey, list<Object*>>* GetEnableObjectList() { return &EnableObjectList; }
	map<eObjectKey, list<Object*>>* GetDisableObjectList() { return &DisableObjectList; }

	// ** map 컨테이너를 사용하고있는 Bridge Enable/Disable List를 반환.
	map<eBridgeKey, list<Bridge*>>* GetEnableBridgeList() { return &EnableBridgeList; }
	map<eBridgeKey, list<Bridge*>>* GetDisableBridgeList() { return &DisableBridgeList; }

	// ** ObjectKey에 해당하는 Object List를 반환
	list<Object*> GetObjectList(eObjectKey _ObjectKey);	

	// ** BridgeKey에 해당하는 Bridge List를 반환
	list<Bridge*> GetBridgeList(eBridgeKey _BridgeKey);

private:
	// ** 오브젝트 객체 생성
	Object* CreateObject(eObjectKey _Key);
	Object* CreateObject(eObjectKey _Key, Vector3 _Position);

	// ** 브릿지 객체 생성
	Bridge* CreateBridge(eBridgeKey _Key);

	// ** 오브젝트 객체 추가
	void AddObject(map<eObjectKey, list<Object*>>& _TargetList, Object* _pObject);

	// ** 브릿지 객체 추가
	void AddBridge(map<eBridgeKey, list<Bridge*>>& _TargetList, Bridge* _pObject);

	// ** 모든 활성화 오브젝트 간 충돌 검사
	void CheckCollision();

private:
	ObjectManager() : pPlayer(nullptr) { }
public:
	~ObjectManager() { Release(); }
};

