#pragma once
#include "Object.h"

class UserInterface : public Object
{
public:
	typedef Object Super;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;
	virtual void OnCollision(Object* _pObject) override;

	virtual Object* Clone() { return new UserInterface(*this); };

public:
	UserInterface();
	virtual ~UserInterface();
};

