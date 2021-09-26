#pragma once
#include "BackgroundBridge.h"

class ScrollVerticalBkg : public BackgroundBridge
{
	enum class eScrollDirection
	{
		UP,
		DOWN,
	};

private:
	float ImageOffset;
	float LoopOffset;

	// ** 스크롤 방향
	eScrollDirection ScrollDirection;	

	// ** 스크롤을 무한 반복할 것 인지
	bool bLoop;

	// ** 시작부분과 끝부분을 동시에 그리는 작업을 진행중인지(이미지의 끝 부분인지)
	bool bDrawEachStartEnd;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render(HDC _hdc)override;
	virtual void Release()override;

public:
	void SetLoop(bool _bLoop) {	bLoop = _bLoop;	}

	void StartTop();
	void StartBottom();
	void ScrollUp();
	void ScrollDown();


public:
	ScrollVerticalBkg();
	virtual ~ScrollVerticalBkg();
};

