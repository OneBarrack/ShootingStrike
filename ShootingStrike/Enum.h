#pragma once

enum class eInputKey
{
	KEY_UP		,
	KEY_DOWN	,
	KEY_LEFT	,
	KEY_RIGHT	,
	KEY_ESCAPE	,
	KEY_SPACE	,
	KEY_ENTER	,
	KEY_LBUTTON	, // ** 마우스 좌측 키 입력 확인.
	KEY_MAX		, // ** 총 Key 개수.
};

enum class eKeyInputState
{
	NONE	,
	DOWN	,
	PRESSED	,
	UP		,
};

enum class eSCENEID
{
	LOGO ,
	MENU ,
	STAGE,
	EXIT ,
};

enum class eObjectKey
{
	NONE			,
	BACKGROUND		,	
	PLAYER			,
	ENEMY			,
	BULLET			,
	FOREGROUND		,
	BUTTON			,
};

enum class eBridgeKey
{
	NONE						,
	BACKGROUND_BASIC			,
	BACKGROUND_SCROLL_HORIZONTAL,
	BACKGROUND_SCROLL_VERTICAL	,
	ENEMY_BOSS					,
	BULLET_NORMAL				,
	BULLET_GUIDE				,
};

enum class eImageKey
{	
	BUFFER		  ,
	BACKGROUND	  ,
	LOGO		  ,
	LOGOBACK	  ,
	STAGEBACK	  ,
	STAGESIDEBACK ,
	STAGECLOUD	  ,
	PLAYBUTTON	  ,
	PLAYER		  ,
	BULLET		  ,
	MOLE		  ,
	EFFECT		  ,
	KEYMAX		  ,
};

enum class eObjectStatus
{
	ACTIVATED	,
	DEACTIVATED	,
	DESTROYED	,
};

enum class eCollisionType
{
	NONE	,
	ELLIPSE	,
	RECT	,
};

enum class eBulletFiringType
{
	NORMAL	,
	GUIDE	,
};