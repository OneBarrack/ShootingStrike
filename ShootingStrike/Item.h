#pragma once
#include "Object.h"

class Item : public Object
{
public:
	typedef Object Super;

private:
	eItemType itemType;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;
	virtual void OnCollision(Object* _pObject) override;

	virtual Object* Clone() { return new Item(*this); };

public:
	eItemType GetItemType() { return itemType; }
	void SetItemType(eItemType _itemType) { itemType = _itemType; }

public:
	Item();
	virtual ~Item();
};

