#define _USE_MATH_DEFINES
#include <d3dx9.h>
#include <math.h>
#include "mydirect3d.h"
#include "zombie.h"
#include "game.h"
#include "model.h"
#include "collider.h"

ZOMBIE::ZOMBIE()
{
	pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	rot = D3DXVECTOR3(0, 0, 0);
	scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

}

void ZOMBIE::TakeDamage(int Damage)
{
	HP -= Damage;
}

ZOMBIE_BASIC::ZOMBIEAI::ZOMBIEAI()
{
	speed = 0.02f;
	//TargetPos = GetPlayerPos();
	rot = D3DXVECTOR3(0, 0, 0);
}

void ZOMBIE_BASIC::ZOMBIEAI::SetPosRot(D3DXVECTOR3 p, D3DXVECTOR3 r)
{
	pos = p;
	rot = r;
}
//FIXME!!
//プレイヤー4つの中で一番近いプレイヤーを選択する
void ZOMBIE_BASIC::ZOMBIEAI::SetTargetPlayer()
{
	targetPos = WhichIsCloser(pos,GetPlayerAPos(),GetPlayerBPos());

}

//プレイヤーに近づく処理
void ZOMBIE_BASIC::ZOMBIEAI::FollowTarget()
{
	float xDistance = targetPos.x - pos.x;
	float zDistance = targetPos.z - pos.z;
	float hypotenuse = sqrt((xDistance * xDistance) + (zDistance * zDistance));

	//プレイヤーを追う
	pos.x += (xDistance / hypotenuse) * speed;
	pos.z += (zDistance / hypotenuse) * speed;
	
	//FIXME!!
	//プレイヤーを向く処理
	rot = RotationFromPos(pos, targetPos);
}

void ZOMBIE_BASIC::SetPosRot(D3DXVECTOR3 p, D3DXVECTOR3 r)
{
	pos = p;
	rot = r;
}

void ZOMBIE_BASIC::Init(D3DXVECTOR3 _pos, D3DXVECTOR3 _rot, D3DXVECTOR3 _scl)
{
	pos = _pos;
	rot = _rot;
	scl = _scl;
	MoveSpeed = 1.0f;
	HP = 40;
	ATK = 5;
	bUsed = false;
	bAttack = true;
}

void ZOMBIE_BASIC::Update()
{
	if (bUsed)
	{
		AI.SetPosRot(pos, rot);
		AI.SetTargetPlayer();
		AI.FollowTarget();
		pos = AI.GetPos();
		rot = AI.GetRot();

		Attack();

		if (HP <= 0)
			bUsed = false;
	}
}

void ZOMBIE_BASIC::Draw()
{
	if (bUsed)
	{
		Model_Render(MODEL_ZOMBIE, pos, rot);
	}
}


void ZOMBIE_BASIC::Attack()
{
	if (bAttack)
	{
		if (CollisionPoint(GetPlayerA()->GetPos(), pos, 0.2f))
		{
			GetPlayerA()->DAMAGE(ATK);
			bAttack = false;
		}

		if (CollisionPoint(GetPlayerB()->GetPos(), pos, 0.2f))
		{
			GetPlayerB()->DAMAGE(ATK);
			bAttack = false;
		}
	}
}

void ZOMBIE_BASIC::CreatZombie(D3DXVECTOR3 _pos)
{
	pos = _pos;
	MoveSpeed = 1.0f;
	HP = 40;
	bUsed = true;
	bAttack = true;
}


D3DXVECTOR3 ZOMBIE::GetPos()
{
	return pos;
}
