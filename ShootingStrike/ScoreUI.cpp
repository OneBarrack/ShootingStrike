#include "ScoreUI.h"
#include "GameDataManager.h"
#include "CollisionManager.h"
#include "BitmapManager.h"

ScoreUI::ScoreUI()
	: pScoreImage(nullptr)
	, pNumberImage(nullptr)
	, numberList(queue<int>())
{

}

ScoreUI::~ScoreUI()
{	
}


void ScoreUI::Initialize()
{
	Super::Initialize();

	pScoreImage = BitmapManager::GetInstance()->GetImage(eImageKey::SCORE);
	pNumberImage = BitmapManager::GetInstance()->GetImage(eImageKey::NUMBER);

	key = eBridgeKey::UI_SCORE;
}

void ScoreUI::Update()
{
	Super::Update();

	MakeScoreNumberList();
}

void ScoreUI::Render(HDC _hdc)
{
	Super::Render(_hdc);

	if ( !pScoreImage || !pNumberImage )
		return;

	// ** Score
	TransparentBlt(_hdc, // ** 최종 출력 위치
		int(pOwner->GetPosition().x - pOwner->GetScale().x),
		int(pOwner->GetPosition().y - pOwner->GetScale().y),
		int(pOwner->GetScale().x),
		int(pOwner->GetScale().y),
		pScoreImage->GetMemDC(),
		0,
		0,
		int(pScoreImage->GetScale().x),
		int(pScoreImage->GetScale().y),
		RGB(255, 0, 255));

	// ** Number
	// ** 뒤에서부터 그리기 위해 Offset을 역순으로 루프
	for ( int offset = 9; offset >= 0; --offset )
	{
		int Num = 0; 

		// ** NumberList의 숫자를 뽑아 차례대로 뒤에서부터 그리고, 
		// ** 숫자가 더 이상 없다면 0으로 채운다
		if ( !numberList.empty() )
		{
			Num = numberList.front();
			numberList.pop();
		}
		
		TransparentBlt(_hdc, // ** 최종 출력 위치
			int((pOwner->GetPosition().x - pOwner->GetScale().x) + ((pNumberImage->GetSegmentationScale().x + 15) * offset)),
			int(pOwner->GetPosition().y),
			int(pNumberImage->GetSegmentationScale().x + 13),
			int(pOwner->GetScale().y),
			pNumberImage->GetMemDC(),
			int(pNumberImage->GetSegmentationScale().x * Num),
			0,
			int(pNumberImage->GetSegmentationScale().x),
			int(pNumberImage->GetScale().y),
			RGB(255, 0, 255));
	}
}

void ScoreUI::Release()
{
	Super::Release();
}

void ScoreUI::MakeScoreNumberList()
{
	int score = GameDataManager::GetInstance()->GetScore();
	while ( score > 0 )
	{
		int iTemp = int(score % 10);
		score /= 10;

		numberList.push(iTemp);
	}
}