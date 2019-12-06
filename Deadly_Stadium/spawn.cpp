#include "spawn.h"
#include "game.h"
#include "collider.h"

SPAWN_POINT::SPAWN_POINT()
{

}

SPAWN_POINT::~SPAWN_POINT()
{

}

void SPAWN_POINT::init(D3DXVECTOR3 _pos)
{
	pos = _pos;
	bUse = true;
}

void SPAWN_POINT::Update()
{
	if (bUse)
	{
		D3DXVECTOR3 PlayerNearby = WhichIsCloser(pos, GetPlayerAPos(), GetPlayerBPos());
		if(CollisionPoint(pos,PlayerNearby,20) && !CollisionPoint(pos, PlayerNearby, 5))
			Spawn();
	}
}

void SPAWN_POINT::Spawn()
{
	if (SpawnTimeCnt <= 0)
	{
		SpawnTimeCnt = SpawnTime;
		ZOMBIE_BASIC* zombie = GetZombieBasic();
		for (int i = 0; i < ZOMBIE_SIZE; i++)
		{
			if (!zombie[i].bUsed)
			{
				zombie[i].CreatZombie(pos);
				break;
			}
		}
	}
	else
	{
		SpawnTimeCnt--;
	}



}

SPAWN_POINT_SPECIAL_BASEBALL::SPAWN_POINT_SPECIAL_BASEBALL()
{
}

SPAWN_POINT_SPECIAL_BASEBALL::~SPAWN_POINT_SPECIAL_BASEBALL()
{

}

void SPAWN_POINT_SPECIAL_BASEBALL::init(D3DXVECTOR3 _pos)
{
	pos = _pos;
	bUse = true;
}

void SPAWN_POINT_SPECIAL_BASEBALL::Update()
{
	Spawn();
}

void SPAWN_POINT_SPECIAL_BASEBALL::Spawn()
{
	if (SpawnTimeCnt < 0)
	{
		SpawnTimeCnt = SpawnTime;
		ZOMBIE_BASEBALL* baseball = GetBaseBallZombie();
		for (int i = 0; i < SPECIALZOMBIE_SIZE; i++)
		{
			if (!baseball[i].bUsed)
			{
				baseball[i].CreatZombie(pos);
				break;
			}
		}
	}
	else
	{
		SpawnTimeCnt--;
	}
}


SPAWN_POINT_SPECIAL_HAMMER::SPAWN_POINT_SPECIAL_HAMMER()
{
}

SPAWN_POINT_SPECIAL_HAMMER::~SPAWN_POINT_SPECIAL_HAMMER()
{

}

void SPAWN_POINT_SPECIAL_HAMMER::init(D3DXVECTOR3 _pos)
{
	pos = _pos;
	bUse = true;
}

void SPAWN_POINT_SPECIAL_HAMMER::Update()
{
	Spawn();
}

void SPAWN_POINT_SPECIAL_HAMMER::Spawn()
{
	if (SpawnTimeCnt < 0)
	{
		SpawnTimeCnt = SpawnTime;
		ZOMBIE_HAMMER* hammer = GetZombieHammer();
		for (int i = 0; i < SPECIALZOMBIE_SIZE; i++)
		{
			if (!hammer[i].bUsed)
			{
				hammer[i].CreatZombie(pos);
				break;
			}
		}
	}
	else
	{
		SpawnTimeCnt--;
	}
}
