#define _USE_MATH_DEFINES

#include <d3dx9.h>
#include <math.h>
#include "mydirect3d.h"
#include "texture.h"
#include "sprite.h"
#include "common.h"
#include "input.h"
#include "Myxinput.h"
#include "camera.h"
#include "arrow.h"
#include "collider.h"
#include "enemy.h"
#include "map.h"
#include "model.h"

ARROW::ARROW()
{
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rot = D3DXVECTOR3(0, 0, 0);
	scl = D3DXVECTOR3(0.1f, 0.05f, 0.8f);
	bUsed = false;
	bPiercing = false;
}

void ARROW::Init()
{

}


void ARROW::Create(bool b ,int a,D3DXVECTOR3 p, D3DXVECTOR3 r)
{
	bPiercing = b;
	ATK = a;
	pos = p;
	rot = r;
	bUsed = true;
}

void ARROW::Update()
{
	if (bUsed)
	{
		oldpos = pos;
		if (bPiercing)
		{
			pos.x += sin(rot.y) * speed / 30.0f;
			pos.z += cos(rot.y) * speed / 30.0f;
		}
		else
		{
			pos.x += sin(rot.y) * speed / 60.0f;
			pos.z += cos(rot.y) * speed / 60.0f;
		}

		ARROW::WallCheck();
		ARROW::OutCheck();
	}

}

void ARROW::Destroy()
{
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rot = D3DXVECTOR3(0, 0, 0);
	bUsed = false;
}

void ARROW::Draw()
{
	if (bUsed)
	{
		Model_Render(MODEL_SAMPLE, pos, rot);
	}

}

void ARROW::OutCheck()
{
	float dx = fabsf(GetCamera().GetPos().x - pos.x);
	float dz = fabsf(GetCamera().GetPos().z - pos.z);
	if (dx > 8.0f || dz > 5.6f)
	{
		Destroy();
	}

}

void ARROW::WallCheck()
{
	if (IsWall(pos.x + 10, pos.z + 10))
	{
		pos.x = oldpos.x;
		pos.z = oldpos.z;
	}
}

bool ARROW::HitCheck()
{
	ZOMBIE_BASIC* zombie = GetZombieBasic();
	for (int i = 0; i < ZOMBIE_SIZE; i++)
	{
		if (zombie[i].bUsed && CollisionPoint(pos, zombie[i].GetPos(),0.3f))
		{
			zombie[i].TakeDamage(ATK);
			if(!bPiercing)
				Destroy();
			return true;
		}
	}

	ZOMBIE_HAMMER* zhammer = GetZombieHammer();
	for (int i = 0; i < SPECIALZOMBIE_SIZE; i++)
	{
		if (zhammer[i].bUsed && CollisionPoint(pos, zhammer[i].GetPos(), 0.3f))
		{
			zhammer[i].TakeDamage(ATK);
			if (!bPiercing)
				Destroy();
			return true;
		}
	}

	ZOMBIE_BASEBALL* zbaseball = GetBaseBallZombie();
	for (int i = 0; i < SPECIALZOMBIE_SIZE; i++)
	{
		if (zbaseball[i].bUsed && CollisionPoint(pos, zbaseball[i].GetPos(), 0.3f))
		{
			zbaseball[i].TakeDamage(ATK);
			if (!bPiercing)
				Destroy();
			return true;
		}
	}

	return false;
}

bool ARROW::isUsed()
{
	return bUsed;
}
