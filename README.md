# ShootingStrike
* A shooting game similar to strikers 1945. * Made for study and portfolio.

프로젝트명 : Shooting Strike  
개발 기간 : 6주  
개발 환경 : C++ / WINAPI / Github  
개발 인원 : 1명  
URL	Video : https://youtu.be/ef5NdgWSevY  
Git Repository :  https://github.com/OneBarrack/ShootingStrike

요약 설명  
ㆍ2D 종스크롤 슈팅 게임으로 스테이지에 등장하는 몬스터들을 모두 처치하는 PC게임  
ㆍ자체 엔진으로 게임을 제작 해 보며 엔진의 간단한 기능 및 구성들을 간소화하여 구현 해보는 학습 목적  

구현 내용  
1) 기본 흐름 및 데이터 형식 설정  
   a. 초기화(Initialize) – 업데이트(Update) – 렌더링(Rendering) – 해제(Release) 의 작동흐름으로 메인 업데이트 구성  
   b. Object Pool 구현하여 Enable / Disable List에서 모든 Object를 관리하도록 구현  
   c. Object들은 브릿지 패턴을 적용하여 기능 – 구현을 분리하여 구현  
   d. 각 매니저 클래스에 Singleton 패턴 적용 (Scene, Input, Render, Bitmap, Collision, Math, Spawn, Sound, GameData, Game Debug)  

2) 전투 시스템  
   a. 필살기 - 맵에 존재하는 모든 적군과 총알이 코인으로 변하여 플레이어에게 이동되도록 구현  
   b. 총알 발사 패턴 및 몬스터 이동 패턴 스크립트를 만들어 구현  
      1. 1자 직진 패턴  
      2. Spin 패턴 – 360도 회전하며 발사  
      3. Multi Spin 패턴 – Spin 패턴을 주기를 두고 여러 번 발사  
      4. N – Polygon 패턴 - N각형의 모형으로 발사  
      5. Back and Forth 패턴 – 좌우로 움직이며 발사  
   c. 충돌 처리  
      1. Collision Manager에서 충돌처리 함수를 관리하도록 구현  
      2. 원 – 원, 사각형 – 사각형, 원 – 사각형, 점 – 원/사각형 충돌 구현  
  
3) 이미지  
    a. Sprite Bitmap 이미지로 애니메이션 효과 구현  
    b. Scene 변경 및 Clear/GameOver 시 Alpha Blend 적용  
    
4) 각종 UI 구현

![image](https://user-images.githubusercontent.com/62101267/141670926-79cd3d8c-4f65-4f73-9477-96f818937f99.png) ![image](https://user-images.githubusercontent.com/62101267/141670934-2c1a188a-a77a-4000-ad00-f5297cbb52bb.png) ![image](https://user-images.githubusercontent.com/62101267/141670939-ff1047e1-258d-43cb-a78d-1e70fd9cbbb6.png) ![image](https://user-images.githubusercontent.com/62101267/141670940-92d57606-16be-4dc5-b7cb-695d82b5ff1c.png) ![image](https://user-images.githubusercontent.com/62101267/141670942-71511633-8829-4fea-addd-024b01e4694a.png) ![image](https://user-images.githubusercontent.com/62101267/141670943-77245071-bc91-4390-bbd3-31340819f1e0.png) ![image](https://user-images.githubusercontent.com/62101267/141670949-c3663f2f-97e0-4839-a03b-a4e8aca03043.png) ![image](https://user-images.githubusercontent.com/62101267/141670952-7aa25a5c-891e-4be4-85e0-dde78642d022.png) ![image](https://user-images.githubusercontent.com/62101267/141670954-4f67c456-31fe-49ed-b61f-93ac1b198487.png) ![image](https://user-images.githubusercontent.com/62101267/141670955-c040a1fa-692b-48e2-a3e9-861396325ceb.png)









