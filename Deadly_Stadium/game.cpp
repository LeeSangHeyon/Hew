#include "common.h"
#include "mydirect3d.h"
#include "Myxinput.h"
#include <d3dx9.h>
#include "UI.h"
#include "camera.h"
#include "light.h"
#include "map.h"
#include "player.h"
#include "field.h"
#include "enemy.h"
#include "helicopter.h"

UI ui;
CAMERA camera;
CLight light;

PLAYER_A player1;
PLAYER_B player2;

void Game_Init()
{
	light.Init();

	Field_Initialize(10, 10, 2, 2);

	InitMap();

	InitHeli();

	player1.Init();

	player2.Init();

	Enemy_Init();

}

void Game_Update(GAMEPAD pad1, GAMEPAD pad2)
{
	camera.GetPlayerPos(player1.GetPos(), player2.GetPos());

	camera.Update();

	UpdateMap();

	UpdateHeli();

	ui.Update(player1.GetStatus(), player2.GetStatus());

	player1.Update(pad1);
	player2.Update(pad2);

	player1.BorderCheck(camera.GetABX(), camera.GetABZ());
	player2.BorderCheck(camera.GetABX(), camera.GetABZ());

	player1.WallCheck();
	player2.WallCheck();

	Enemy_Update();
}

void Game_Draw()
{

	camera.Set();

	Field_Draw();

	light.Set(true);

	DrawMap();

	DrawHeli();

	player1.Draw();

	player2.Draw();

	Enemy_Draw();

	ui.Draw();
}

CAMERA GetCamera()
{
	return camera;
}

PLAYER_A* GetPlayerA()
{
	return &player1;
}

PLAYER_B* GetPlayerB()
{
	return &player2;
}

D3DXVECTOR3 GetPlayerAPos()
{
	return player1.GetPos();
}

D3DXVECTOR3 GetPlayerBPos()
{
	return player2.GetPos();
}

D3DXVECTOR3 GetCameraPos()
{
	return camera.GetPos();
}