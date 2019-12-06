#define _USE_MATH_DEFINES

#include <d3dx9.h>
#include <math.h>
#include "mydirect3d.h"
#include "texture.h"
#include "sprite.h"
#include "common.h"
#include "input.h"
#include "Myxinput.h"
#include "map.h"
#include "collider.h"
#include "player.h"
#include "enemy.h"
#include "model.h"
#include "arrow.h"

ARROW arrow[MAX_ARROW];

PLAYER::PLAYER()
{
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rot = D3DXVECTOR3(0, 0, 0);
	scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	status.HP = 100;
	status.reg_HP = 100;
	status.SP = 0;
	status.LVL = 1;
	status.EXP = 0;
	status.ATK = 10;

	status.bSkill = false;
}


void PLAYER::BorderCheck(float abx, float abz)
{
	if (abx > 14.9f)
	{
		pos.x = oldpos.x;
	}

	if (abz > 8.9f)
	{
		pos.z = oldpos.z;
	}
}

void PLAYER::WallCheck()
{
	if (IsWall(pos.x + 10, pos.z + 10))
	{
		pos.x = oldpos.x;
		pos.z = oldpos.z;
	}

	if (CollisionPoint(pos,GetTorchPos(),0.6f))
	{
		pos.x = oldpos.x;
		pos.z = oldpos.z;
	}
}


void PLAYER::EXP_UP(int exp)
{
	status.EXP += exp;
	if (status.EXP > 100)
		status.EXP = 100;
}

void PLAYER::SP_UP(int sp)
{
	status.SP += sp;
	if (status.SP >= 100)
	{
		status.bSkill = true;
		status.SP = 100;
	}
}

void PLAYER::DAMAGE(int dmg)
{
	status.HP -= dmg;
	if(status.HP < 0)
		status.HP = 0;
}

PLAYER_A::PLAYER_A()
{
	pos = D3DXVECTOR3(-6.5f, 0.0f, -8.0f);
	rot = D3DXVECTOR3(0, 0, 0);
	scl = D3DXVECTOR3(3, 3, 3);

	bAiming = false;
}

void PLAYER_A::Init()
{

}

void PLAYER_A::Update(GAMEPAD pad)
{
	oldpos = pos;

	if (Keyboard_IsPress(DIK_W))
	{
		pos.z += speed / 60.0f;
		rot.y = 0;
	}
	if (Keyboard_IsPress(DIK_S))
	{
		pos.z -= speed / 60.0f;
		rot.y = M_PI;
	}
	if (Keyboard_IsPress(DIK_D))
	{
		pos.x += speed / 60.0f;
		rot.y = M_PI / 2;
	}
	if (Keyboard_IsPress(DIK_A))
	{
		pos.x -= speed / 60.0f;
		rot.y = 3 * M_PI / 2;
	}

	//左スティックの取得
	Stick Lstick = pad.GetLeftStick();

	if (Lstick.x || Lstick.y)
	{
		pos.x += Lstick.x / hypotf(Lstick.x, Lstick.y) * speed / 60.0f;
		pos.z += Lstick.y / hypotf(Lstick.x, Lstick.y) * speed / 60.0f;
		rot.y = (Lstick.y > 0) ? asinf(Lstick.x / hypotf(Lstick.x, Lstick.y)) : M_PI + asinf(-Lstick.x / hypotf(Lstick.x, Lstick.y));
	}

	//右スティックの取得
	Stick Rstick = pad.GetRightStick();

	if (Rstick.x || Rstick.y)
	{
		rot.y = (Rstick.y > 0) ? asinf(Rstick.x / hypotf(Rstick.x, Rstick.y)) : M_PI + asinf(-Rstick.x / hypotf(Rstick.x, Rstick.y));
	}

	//SHOULDER
	if (pad.GetKeyRelease(XINPUT_GAMEPAD_RIGHT_SHOULDER) || Keyboard_IsTrigger(DIK_Z))
	{
		int cnt = 0;
		for (int i = 0; i < MAX_ARROW; i++)
		{
			if (!arrow[i].isUsed())
			{
				arrow[i].Create(false,status.ATK, pos + D3DXVECTOR3(0.4f * sinf(rot.y), 0, 0.4f * cosf(rot.y)), rot + D3DXVECTOR3(0, cnt * M_PI / 10 - M_PI / 10, 0));
				cnt++;
			}
			if (cnt >= 3)
			{
				break;
			}
		}
	}

	for (int i = 0; i < MAX_ARROW; i++)
	{
		if (arrow[i].isUsed())
		{
			arrow[i].Update();
			if (arrow[i].HitCheck())
			{
				SP_UP(1);
				EXP_UP(1);
			}
		}
	}

	//

	if (pad.GetRightTrigger() > 0 || Keyboard_IsPress(DIK_Z))
	{
		bAiming = true;
	}
	else
	{
		bAiming = false;
	}

	if (pad.GetRightRelease())
	{
		for (int i = 0; i < MAX_ARROW; i++)
		{
			if (!arrow[i].isUsed())
			{
				arrow[i].Create(true, 2 * status.ATK, pos + D3DXVECTOR3(0.4f * sinf(rot.y), 0 , 0.4f * cosf(rot.y)), rot);
				break;
			}
		}
	}

}

void PLAYER_A::Draw()
{
	if(bAiming)
		Line_Draw(pos, rot);

	Model_Render(MODEL_BOXER, pos, rot);
	Model_Render(MODEL_BOW, pos, rot);

	for (int i = 0; i < MAX_ARROW; i++)
	{
		if (arrow[i].isUsed())
		{
			arrow[i].Draw();
		}
	}
}

PLAYER_B::PLAYER_B()
{
	pos = D3DXVECTOR3(-5.5f, 0.0f, -8.0f);
	rot = D3DXVECTOR3(0, 0, 0);
	scl = D3DXVECTOR3(3, 3, 3);
	 
	status.ATK = 15;
}

void PLAYER_B::Init()
{

}

void PLAYER_B::Update(GAMEPAD pad)
{
	oldpos = pos;

	if (Keyboard_IsPress(DIK_UP))
	{
		pos.z += speed / 60.0f;
	}
	if (Keyboard_IsPress(DIK_DOWN))
	{
		pos.z -= speed / 60.0f;
	}
	if (Keyboard_IsPress(DIK_RIGHT))
	{
		pos.x += speed / 60.0f;
	}
	if (Keyboard_IsPress(DIK_LEFT))
	{
		pos.x -= speed / 60.0f;
	}

	//左スティックの取得
	Stick Lstick = pad.GetLeftStick();
	if (Lstick.x || Lstick.y)
	{
		pos.x += Lstick.x / hypotf(Lstick.x, Lstick.y) * speed / 60.0f;
		pos.z += Lstick.y / hypotf(Lstick.x, Lstick.y) * speed / 60.0f;
		rot.y = (Lstick.y > 0) ? asinf(Lstick.x / hypotf(Lstick.x, Lstick.y)) : M_PI + asinf( -Lstick.x / hypotf(Lstick.x, Lstick.y));
	}

	//右スティックの取得
	Stick Rstick = pad.GetRightStick();

	if (Rstick.x || Rstick.y)
	{
		rot.y = (Rstick.y > 0) ? asinf(Rstick.x / hypotf(Rstick.x, Rstick.y)) : M_PI + asinf( -Rstick.x / hypotf(Rstick.x, Rstick.y));
	}

	if (pad.GetKeyRelease(XINPUT_GAMEPAD_RIGHT_SHOULDER) || Keyboard_IsTrigger(DIK_X))
	{
		HitCheck();
	}

}

void PLAYER_B::Draw()
{
	Model_Render(MODEL_FENCING, pos, rot);

	Model_Render(MODEL_SWORD, pos + D3DXVECTOR3(0.2f * sinf(rot.y), 0, 0.2f * cosf(rot.y)), rot);
}

void PLAYER_B::HitCheck()
{
	ZOMBIE_BASIC* zombie = GetZombieBasic();
	for (int i = 0; i < ZOMBIE_SIZE; i++)
	{
		if (zombie[i].bUsed && CollisionPoint(pos, zombie[i].GetPos(), 2.0f))
		{
			zombie[i].TakeDamage(status.ATK);
			SP_UP(1);
			EXP_UP(1);
		}
	}

	ZOMBIE_HAMMER* zhammer = GetZombieHammer();
	for (int i = 0; i < SPECIALZOMBIE_SIZE; i++)
	{
		if (zhammer[i].bUsed && CollisionPoint(pos, zhammer[i].GetPos(), 2.0f))
		{
			zhammer[i].TakeDamage(status.ATK);
			SP_UP(1);
			EXP_UP(1);
		}
	}

	ZOMBIE_BASEBALL* zbaseball = GetBaseBallZombie();
	for (int i = 0; i < SPECIALZOMBIE_SIZE; i++)
	{
		if (zbaseball[i].bUsed && CollisionPoint(pos, zbaseball[i].GetPos(), 2.0f))
		{
			zbaseball[i].TakeDamage(status.ATK);
			SP_UP(1);
			EXP_UP(1);
		}
	}
}
