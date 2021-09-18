#pragma once
#include "Object.h"
#include "Bridge.h"

template <typename T>
class ObjectFactory
{
public:
	static Object* CreateObject(Bridge* _pBridge = nullptr)
	{
		Object* pObj = new T;
		pObj->Initialize();

		if ( _pBridge )
		{
			_pBridge->SetObject(pObj);
			_pBridge->Initialize();

			((T*)pObj)->SetBridge(_pBridge);
		}

		return pObj;
	}

	static Object* CreateObject(Vector3 _vPos, Bridge* _pBridge = nullptr)
	{
		Object* pObj = new T;
		pObj->Initialize();
		pObj->SetPosition(_vPos);

		if ( _pBridge )
		{
			_pBridge->SetObject(pObj);
			_pBridge->Initialize();

			((T*)pObj)->SetBridge(_pBridge);
		}

		return pObj;
	}
};