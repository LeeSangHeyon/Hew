#include <d3dx9.h>
#include <math.h>
#include "mydirect3d.h"
#include "sprite.h"
#include "texture.h"
#include "common.h"
#include "player.h"
#include "collider.h"
#include "map.h"
#include "game.h"
#include "UI.h"
#include "helicopter.h"

bool bCountDown = false;

UI::UI()
{
	bClear = false;
	Count = 3600;
}

void UI::Init()
{

}

void UI::Update(PLAYER_STATUS p1, PLAYER_STATUS p2)
{
	player1 = p1;
	player2 = p2;

	if (CollisionPoint(GetCameraPos(),GetTorchPos(),3.0f) && !bCountDown)
	{
		bCountDown = true;
	}

	if (bCountDown)
	{
		Count--;
		if (Count <= 0)
		{
			bCountDown = false;
			bClear = true;
			SetHeli();
		}
	}
}

void UI::Draw()
{
	//Player1

	//HP UNDERBAR
	Sprite_SetColor(D3DCOLOR_RGBA(240, 40, 10, 255));
	SpriteA_Draw(TEXTURE_INDEX_UNDERBAR, SCREEN_WIDTH / 18 + 34, SCREEN_HEIGHT * 5 / 6 - 23, 0, 0, 262, 26);
	//HP BAR
	Sprite_SetColor(D3DCOLOR_RGBA(240, 40, 10, 255));
	SpriteA_Draw(TEXTURE_INDEX_BAR, SCREEN_WIDTH / 18 + 34, SCREEN_HEIGHT * 5 / 6 - 22, 0, 0, 260 * player1.HP / 100, 24);
	//EXP UNDERBAR
	Sprite_SetColor(D3DCOLOR_RGBA(246, 190, 10, 255));
	SpriteA_Draw(TEXTURE_INDEX_UNDERBAR, SCREEN_WIDTH / 18 + 34, SCREEN_HEIGHT * 5 / 6 + 3, 0, 16, 262, 10);
	//EXP BAR
	Sprite_SetColor(D3DCOLOR_RGBA(246, 190, 10, 255));
	SpriteA_Draw(TEXTURE_INDEX_BAR, SCREEN_WIDTH / 18 + 34, SCREEN_HEIGHT * 5 / 6 + 4, 0, 16, 260 * player1.EXP / 100, 8);
	//UNDER ICON
	Sprite_SetColor(D3DCOLOR_RGBA(0, 250, 10, 255));
	Sprite_Draw(TEXTURE_INDEX_PLAYERICON, SCREEN_WIDTH / 18, SCREEN_HEIGHT * 5 / 6 , 0, 0, 80, 80);
	//SKILL BAR
	Sprite_SetColor(D3DCOLOR_RGBA(250, 160, 20, 255));
	SpriteB_Draw(TEXTURE_INDEX_SKILLHUD, SCREEN_WIDTH / 18 - 36, SCREEN_HEIGHT * 5 / 6 + 36 , 0, 0, 72, 72 * player1.SP / 100);
	//PROF ICON
	if(player1.bSkill)
		Sprite_SetColor(D3DCOLOR_RGBA(0, 180, 6, 255));
	else
		Sprite_SetColor(D3DCOLOR_RGBA(10, 10, 10, 255));
	Sprite_Draw(TEXTURE_INDEX_BOW, SCREEN_WIDTH / 18, SCREEN_HEIGHT * 5 / 6, 0, 0, 50, 50);


	//Player2

	//HP UNDERBAR
	Sprite_SetColor(D3DCOLOR_RGBA(240, 40, 10, 255));
	SpriteA_Draw(TEXTURE_INDEX_UNDERBAR, SCREEN_WIDTH * 5 / 18 + 34, SCREEN_HEIGHT * 5 / 6 - 23, 0, 0, 262, 26);
	//HP BAR
	Sprite_SetColor(D3DCOLOR_RGBA(240, 40, 10, 255));
	SpriteA_Draw(TEXTURE_INDEX_BAR, SCREEN_WIDTH * 5/ 18 + 34, SCREEN_HEIGHT * 5 / 6 - 22, 0, 0, 260 * player2.HP / 100, 24);
	//EXP UNDERBAR
	Sprite_SetColor(D3DCOLOR_RGBA(246, 190, 10, 255));
	SpriteA_Draw(TEXTURE_INDEX_UNDERBAR, SCREEN_WIDTH * 5 / 18 + 34, SCREEN_HEIGHT * 5 / 6 + 3, 0, 16, 262, 10);
	//EXP BAR
	Sprite_SetColor(D3DCOLOR_RGBA(246, 190, 10, 255));
	SpriteA_Draw(TEXTURE_INDEX_BAR, SCREEN_WIDTH * 5 / 18 + 34, SCREEN_HEIGHT * 5 / 6 + 4, 0, 16, 260 * player2.EXP / 100, 8);
	//UNDER ICON
	Sprite_SetColor(D3DCOLOR_RGBA(50, 200, 240, 255));
	Sprite_Draw(TEXTURE_INDEX_PLAYERICON, SCREEN_WIDTH * 5 / 18, SCREEN_HEIGHT * 5 / 6, 0, 0, 80, 80);
	//SKILL BAR
	Sprite_SetColor(D3DCOLOR_RGBA(250, 160, 20, 255));
	SpriteB_Draw(TEXTURE_INDEX_SKILLHUD, SCREEN_WIDTH * 5 / 18 - 36, SCREEN_HEIGHT * 5 / 6 + 36, 0, 0, 72, 72 * player2.SP / 100);
	//PROF ICON
	if (player2.bSkill)
		Sprite_SetColor(D3DCOLOR_RGBA(30, 120, 160, 255));
	else
		Sprite_SetColor(D3DCOLOR_RGBA(10, 10, 10, 255));
	Sprite_Draw(TEXTURE_INDEX_FENCING, SCREEN_WIDTH * 5 / 18, SCREEN_HEIGHT * 5 / 6, 0, 0, 56, 56);

	if (bCountDown)
	{
		Sprite_SetColor(D3DCOLOR_RGBA(60 + Count / 15, 60, 180, 255));
		SpriteA_Draw(TEXTURE_INDEX_BAR, SCREEN_WIDTH * 5 / 12, SCREEN_HEIGHT * 1 / 6, 0, 4, 260 * Count / 2400, 16);
	}
	
}

bool GetTorchStart()
{
	return bCountDown;
}