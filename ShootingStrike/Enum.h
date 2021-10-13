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
	ENEMY_NORMAL				,
	ENEMY_GO_AND_SPIN			,
	ENEMY_BACK_AND_FORTH		,
	BULLET_NORMAL				,
	BULLET_GUIDE				,
	BULLET_GO_TARGET_AFTER_DELAY,
	BULLET_SPREAD_AFTER_DELAY	,
	UI_BUTTON					,
	UI_SCORE					,
	UI_TEXT						,
	UI_LIFE						,
	UI_PROGRESSBAR				,
	UI_MAP_PROGRESS			,
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
	PROGRESSBAR	  ,
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

enum class eBulletSpawnPattern
{
	NONE						,
	SPIN_GO						,
	MULTI_SPIN_GO				,
	N_POLYGON_GO				,
	CIRCLE_GO					,
	CIRCLE_GO_DELAY_GO_TARGET	,
	CIRCLE_STOP_DELAY_GO_TARGET	,
	CIRCLE_GO_DELAY_SPREAD		,
};

enum class eEnemySpawnPattern
{
	NONE						 ,
	FALLDOWN_GO					 ,
	FALLDOWN_GO_RAND			 ,
	FALLDOWN_GO_ACCELERATION	 ,
	FALLDOWN_GO_ACCELERATION_RAND,
	FALLDOWN_BACK_AND_FORTH		 ,
	FALLDOWN_GO_AND_SPIN		 ,
};

enum class eTagName
{
	NONE			,
	STAGE_MAIN_BKG	,
	PLAYER_FLIGHT1	,
	ENEMY_BOSS		,
};