#pragma once

#include "common.h"
#include "mydirect3d.h"
#include "Myxinput.h"
#include "player.h"
#include "camera.h"
#include <d3dx9.h>

void Game_Init();
void Game_Update(GAMEPAD pad1, GAMEPAD pad2);
void Game_Draw();

CAMERA GetCamera();
PLAYER_A* GetPlayerA();
PLAYER_B* GetPlayerB();
D3DXVECTOR3 GetPlayerAPos();
D3DXVECTOR3 GetPlayerBPos();
D3DXVECTOR3 GetCameraPos();