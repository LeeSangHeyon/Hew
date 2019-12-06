#pragma once

#include <d3dx9.h>
#include "enemy.h"
#include "map.h"

class SPAWN_POINT
{
public:
	D3DXVECTOR3 pos;	//SPAWN‚·‚éˆÊ’u

	bool bUse = false;

	float SpawnTime = 50;
	float SpawnTimeCnt = 100;
	SPAWN_POINT();
	~SPAWN_POINT();

public:
	void init(D3DXVECTOR3 _pos);
	void Update();
	void Spawn();

private:

};


class SPAWN_POINT_SPECIAL_BASEBALL
{
public:
	D3DXVECTOR3 pos;	//SPAWN‚·‚éˆÊ’u

	bool bUse = false;

	float SpawnTime = 1000;
	float SpawnTimeCnt = 2000;
	SPAWN_POINT_SPECIAL_BASEBALL();
	~SPAWN_POINT_SPECIAL_BASEBALL();

public:
	void init(D3DXVECTOR3 _pos);
	void Update();
	void Spawn();

private:

};

class SPAWN_POINT_SPECIAL_HAMMER
{
public:
	D3DXVECTOR3 pos;	//SPAWN‚·‚éˆÊ’u

	bool bUse = false;

	float SpawnTime = 1000;
	float SpawnTimeCnt = 2000;
	SPAWN_POINT_SPECIAL_HAMMER();
	~SPAWN_POINT_SPECIAL_HAMMER();

public:
	void init(D3DXVECTOR3 _pos);
	void Update();
	void Spawn();

private:

};
