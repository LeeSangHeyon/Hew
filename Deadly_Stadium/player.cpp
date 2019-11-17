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
#include "map.h"
#include "player.h"
#include "xfile.h"
#include "arrow.h"


XFile p_model;
ARROW arrow[MAX_ARROW];

PLAYER::PLAYER()
{
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rot = D3DXVECTOR3(0, 0, 0);
	scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

}


void PLAYER::Init()
{
	
	p_model.init("asset/model/test.x");
	for (int i = 0; i < MAX_ARROW; i++)
	{
		arrow->Init();
	}
}


void PLAYER::Draw()
{
	p_model.set(pos, rot, scl);
	p_model.draw();

	for (int i = 0; i < MAX_ARROW; i++)
	{
		if (arrow[i].isUsed())
		{
			arrow[i].Draw();
		}
	}
}

void PLAYER::BorderCheck(float abx, float abz)
{
	if (abx >= 15.0f)
	{
		pos.x = oldpos.x;
	}

	if (abz >= 9.0f)
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
}

D3DXVECTOR3 PLAYER::GetPos()
{
	return pos;
}


PLAYER_A::PLAYER_A()
{
	pos = D3DXVECTOR3(-0.5f, 0.0f, 0.0f);
	rot = D3DXVECTOR3(0, 0, 0);
	scl = D3DXVECTOR3(30, 30, 30);
}

void PLAYER_A::Update(GAMEPAD pad)
{
	oldpos = pos;

	if (Keyboard_IsPress(DIK_W))
	{
		pos.z += speed / 60.0f;
	}
	if (Keyboard_IsPress(DIK_S))
	{
		pos.z -= speed / 60.0f;
	}
	if (Keyboard_IsPress(DIK_D))
	{
		pos.x += speed / 60.0f;
	}
	if (Keyboard_IsPress(DIK_A))
	{
		pos.x -= speed / 60.0f;
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

	if (pad.GetKeyUp(XINPUT_GAMEPAD_RIGHT_SHOULDER) || Keyboard_IsTrigger(DIK_Z))
	{
		for (int i = 0; i < MAX_ARROW; i++)
		{
			if (!arrow[i].isUsed())
			{
				arrow[i].Create(pos,rot);
				break;
			}
		}
	}

	for (int i = 0; i < MAX_ARROW; i++)
	{
		arrow[i].Update();
	}

}

PLAYER_B::PLAYER_B()
{
	pos = D3DXVECTOR3(0.5f, 0.0f, 0.0f);
	rot = D3DXVECTOR3(0, 0, 0);
	scl = D3DXVECTOR3(30, 30, 30);
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
		rot.y = (Lstick.y > 0) ? asinf(Lstick.x / hypotf(Lstick.x, Lstick.y)) : M_PI + asinf(-Lstick.x / hypotf(Lstick.x, Lstick.y));
	}

	//右スティックの取得
	Stick Rstick = pad.GetRightStick();

	if (Rstick.x || Rstick.y)
	{
		rot.y = (Rstick.y > 0) ? asinf(Rstick.x / hypotf(Rstick.x, Rstick.y)) : M_PI + asinf(- Rstick.x / hypotf(Rstick.x, Rstick.y));
	}

}