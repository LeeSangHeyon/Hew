#include <d3dx9.h>
#include <math.h>
#include "mydirect3d.h"
#include "texture.h"
#include "sprite.h"
#include "common.h"
#include "input.h"
#include "Myxinput.h"
#include "model.h"
#include "spawn.h"
#include "UI.h"

#define SPAWN_POINT_SIZE (20)
#define BASIC_SPAWN_POINT_SIZE (5)
#define SPECIAL_SPAWN_POINT_SIZE (5)


SPAWN_POINT SpawnPoint[SPAWN_POINT_SIZE];
SPAWN_POINT_SPECIAL_BASEBALL SpawnPointSpecial_BASEBALL[SPECIAL_SPAWN_POINT_SIZE];
SPAWN_POINT_SPECIAL_HAMMER SpawnPointSpecial_HAMMER[SPECIAL_SPAWN_POINT_SIZE];

D3DXVECTOR3 torchPos;

bool LastFlag = true;

char map_text[20][20 + 1]
{
	" g  1  g     g  1 g ",
	"g                  g",
	"     2              ",
	"                    ",
	"g         o       g ",
	"                    ",
	" 1            2   g ",
	" g                  ",
	" g g           g g  ",
	"         g g        ",
	"  g             g   ",
	"                    ",
	"                    ",
	"*******     ********",
	"*     *            *",
	"*     *            *",
	"****************   *",
	"*                x *",
	"*                  *",
	"********************",

};

bool IsWall(int x, int y)
{
	if (map_text[19 - y][x] == '*')
	{
		return true;
	}
	else
	{
		return false;
	}

}

void SetTorch()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (map_text[19 - j][i] == 'o')
			{
				torchPos = {i - 9.5f ,1,j - 9.5f };
				break;
			}

		}
	}
}

D3DXVECTOR3 GetTorchPos()
{
	return torchPos;
}

bool IsSpawn(int x, int y)
{
	if (map_text[19 - y][x] == 'x')
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool IsLastSpawn(int x, int y)
{
	if (map_text[19 - y][x] == 'g')
	{
		return true;
	}
	else
	{
		return false;
	}

}

void InitMap()
{
	SetSpawnPoint();
	SetTorch();
}

void UpdateMap()
{

	if (GetTorchStart() && LastFlag)
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (IsLastSpawn(i, j) && LastFlag)
				{
					for (int k = 0; k < SPAWN_POINT_SIZE; k++)
					{
						if (!SpawnPoint[k].bUse)
						{
							SpawnPoint[k].init(D3DXVECTOR3(i - 9.5f, 0, j - 9.5f));
							break;
						}
					}
				}

			}
		}

		LastFlag = false;
	}

	for (int k = 0; k < BASIC_SPAWN_POINT_SIZE; k++)
	{
		if (SpawnPoint[k].bUse)
		{
			SpawnPoint[k].Update();
		}
	}

	for (int k = 0; k < SPECIAL_SPAWN_POINT_SIZE; k++)
	{
		if (SpawnPointSpecial_BASEBALL[k].bUse)
		{
			SpawnPointSpecial_BASEBALL[k].Update();
		}
	}

	for (int k = 0; k < SPECIAL_SPAWN_POINT_SIZE; k++)
	{
		if (SpawnPointSpecial_HAMMER[k].bUse)
		{
			SpawnPointSpecial_HAMMER[k].Update();
		}
	}


}

void DrawMap()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (IsWall(i, j))
			{
				//wall.set({ (float)i - 9.5f ,0.5, (float)j - 9.5f }, { 0,0,0 }, { 0.499,1,0.499 });
				//wall.draw();
				Model_Render(MODEL_WALL, { (float)i - 9.5f ,0.5, (float)j - 9.5f }, { 0,0,0 });
			}

		}
	}

	//torch.set(torchPos, { 0,0,0 }, { 0.499,0.8,0.499 });
	//torch.draw();
	Model_Render(MODEL_TORCH, torchPos, { 0,0,0 });
}

void SetSpawnPoint()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (IsSpawn(i,j))
			{
				for (int k = 0; k < SPAWN_POINT_SIZE; k++)
				{
					if (!SpawnPoint[k].bUse)
					{
						SpawnPoint[k].init(D3DXVECTOR3(i - 9.5f, 0, j - 9.5f));
						break;
					}
				}
			}

			//Specil Zombie Spawn
			if (map_text[20 - i][j] == '1')
			{
				for (int k = 0; k < SPECIAL_SPAWN_POINT_SIZE; k++)
				{
					if (!SpawnPointSpecial_BASEBALL[k].bUse)
					{
						SpawnPointSpecial_BASEBALL[k].init(D3DXVECTOR3(j - 9.5f, 0, i - 9.5f));
						break;
					}
				}
			}

			//Specil Zombie Spawn
			if (map_text[20 - i][j] == '2')
			{
				for (int k = 0; k < SPECIAL_SPAWN_POINT_SIZE; k++)
				{
					if (!SpawnPointSpecial_HAMMER[k].bUse)
					{
						SpawnPointSpecial_HAMMER[k].init(D3DXVECTOR3(j - 9.5f, 0, i - 9.5f));
						break;
					}
				}
			}


		}
	}
}