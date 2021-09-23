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
	Prototype* PrototypeObject;

	// ** 플레이어
	Object* pPlayer;

	// ** 오브젝트 리스트
	vector<Object*> EnemyList;
	vector<Object*> BulletList;
	map<eObjectKey, list<Object*>> EnableList;
	map<eObjectKey, list<Object*>> DisableList;

public:
	// ** 초기화
	void Initialize();	

	// ** 컨테이너에서 객체를 찾아서 반환. 없다면 Prototype 생성 후 반환
	Object* TakeObject(eObjectKey _Key, Bridge* _pBridge = nullptr);
	Object* TakeObject(eObjectKey _Key, Vector3 _Position, Bridge* _pBridge = nullptr);
	
	// ** 사용후 더이상 사용하지 않는 오브젝트 회수
	void RecallObject(Object* _pObject);

	// ** ObjectKey에 해당하는 Object List를 반환
	list<Object*> GetObjectList(eObjectKey _ObjectKey);

	void Release();

private:
	// ** 객체 생성
	Object* CreateObject(eObjectKey _Key);
	Object* CreateObject(eObjectKey _Key, Vector3 _Position);

	// ** 객체 추가.
	void AddObject(map<eObjectKey, list<Object*>>& _TargetList, Object* _pObject);
public:
	// ** 플레이어를 반환.
	Object* GetPlayer() { return pPlayer; }
	void SetPlayer(Object* _pPlayer) { pPlayer = _pPlayer; }

	// ** map 컨테이너를 사용하고있는 ObjectList를 반환.
	map<eObjectKey, list<Object*>>* GetEnableList() { return &EnableList; }
	map<eObjectKey, list<Object*>>* GetDisableList() { return &DisableList; }
		
	vector<Object*>* GetBulletList() { return &BulletList; }
	vector<Object*>* GetEnemyList() { return &EnemyList; }
private:
	ObjectManager() : pPlayer(nullptr) { }
public:
	~ObjectManager() { Release(); }
};

