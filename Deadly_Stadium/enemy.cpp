#include "zombie.h"
#include "zombie_special.h"
#include "enemy.h"
//#include "zombie_special.h"
#include <d3dx9.h>

ZOMBIE_BASEBALL BaseBallZombie[ZOMBIE_SIZE];
ZOMBIE_BASIC a[SPECIALZOMBIE_SIZE];
ZOMBIE_HAMMER HammerZombie[SPECIALZOMBIE_SIZE];

void Enemy_Init()
{
	for (int i = 0; i < ZOMBIE_SIZE; i++)
	{
		a[i].Init(D3DXVECTOR3(2 * i, 0, 3 * i), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(3.0f, 3, 3.0f));
	}

	for (int i = 0; i < SPECIALZOMBIE_SIZE; i++)
	{
		HammerZombie[i].Init(D3DXVECTOR3(2 + 2 * i, 0, 2 + 2 * i), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(4.0f, 4, 4.0f));
	}

	for (int i = 0; i < SPECIALZOMBIE_SIZE; i++)
	{
		BaseBallZombie[i].Init(D3DXVECTOR3(2 + 2 * i, 0, 2 + 2 * i), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(4.0f, 4, 4.0f));
	}
	Init_Hammer();
	
}

void Enemy_Update()
{
	for (int i = 0; i < ZOMBIE_SIZE; i++)
	{
		a[i].Update();
	}
	for (int i = 0; i < SPECIALZOMBIE_SIZE; i++)
	{
		HammerZombie[i].Update();
	}
	for (int i = 0; i < SPECIALZOMBIE_SIZE; i++)
	{
		BaseBallZombie[i].Update();
	}
	Update_Hammer();
}

void Enemy_Draw()
{
	for (int i = 0; i < ZOMBIE_SIZE; i++)
	{
		a[i].Draw();
	}

	for (int i = 0; i < SPECIALZOMBIE_SIZE; i++)
	{
		HammerZombie[i].Draw();
	}
	for (int i = 0; i < SPECIALZOMBIE_SIZE; i++)
	{
		BaseBallZombie[i].Draw();
	}

	Draw_Hammer();
}

ZOMBIE_BASIC* GetZombieBasic()
{
	return a;
}

ZOMBIE_HAMMER* GetZombieHammer()
{
	return HammerZombie;
}

ZOMBIE_BASEBALL* GetBaseBallZombie()
{
	return BaseBallZombie;
}