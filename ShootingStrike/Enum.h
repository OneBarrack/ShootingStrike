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
	KEY_F8		,
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
	UI				,	
	EFFECT			,
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
	UI_BUTTON					,
	UI_SCORE					,
	UI_TEXT						,
	UI_LIFE						,
	EFFECT_EXPLOSION			,
	EFFECT_HIT					,
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
	TEXT		  ,
	SCORE		  ,
	NUMBER		  ,
	PLAYBUTTON	  ,
	PLAYER		  ,
	BULLET		  ,
	ANGEL		  ,
	HIT			  ,
	EXPLOSION	  ,	
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

enum class eBulletType
{
	NORMAL	,
	GUIDE	,
};

enum class eBulletSpawnPattern
{
	NONE		,
	SPIN		,
	MULTI_SPIN	,
	CIRCLE		,

};

enum class eTagName
{
	NONE			,
	STAGE_MAIN_BKG	,
	PLAYER_FLIGHT1	,
	ENEMY_BOSS		,
};