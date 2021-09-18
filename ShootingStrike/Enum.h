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

enum class eKeyInputStatus
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
	BACKGROUND	,
	PLAYER		,
	ENEMY		,
	ENEMYHOLE	,
	BULLET		,
	HAMMEREFFECT,
};

enum class eImageKey
{	
	BUFFER		  ,
	BACKGROUND	  ,
	SIDEBACKGROUND,
	PLAYER		  ,
	STAGEBACK	  ,
	HAMMER		  ,
	MOLE		  ,
	HOLE		  ,
	EFFECT		  ,
	KEYMAX		  ,
};

enum class eObjectStatus
{
	ACTIVATED	,
	DEACTIVATED	,
	INVISIBLE	,
	DESTROYED	,
};

enum class eCollisionType
{
	NONE	,
	ELLIPSE	,
	RECT	,
};