#pragma once

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
	BUFFER		,
	BACKGROUND	,
	HAMMER		,
	MOLE		,
	HOLE		,
	EFFECT		,
	KEYMAX		,
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