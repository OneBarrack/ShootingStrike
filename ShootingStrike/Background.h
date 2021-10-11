#pragma once
#include "Object.h"

class Background : public Object
{
public:
	typedef Object Super;

private:
	float mapProgressRatio;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;
	virtual void OnCollision(Object* _pObject) override;

	virtual Object* Clone() { return new Background(*this); };

public:
	float GetMapProgressRatio() { return mapProgressRatio; }
	void setMapProgressRatio(float _percentage) { mapProgressRatio = _percentage; }

public:
	Background();
	virtual ~Background();
};