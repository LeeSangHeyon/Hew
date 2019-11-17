#include <d3dx9.h>
#include <math.h>
#include "mydirect3d.h"
#include "texture.h"
#include "sprite.h"
#include "common.h"
#include "input.h"
#include "Myxinput.h"
#include "xfile.h"

XFile ground;
XFile wall;

char map_text[20][20 + 1]
{
	"********************",
	"*                  *",
	"*  **************  *",
	"*  *            *  *",
	"*  *            *  *",
	"*  *            *  *",
	"*  *            *  *",
	"*                  *",
	"*                   ",
	"*                  *",
	"*                  *",
	"*      *******     *",
	"*                  *",
	"*   ****************",
	"*   *************  *",
	"*   *************  *",
	"*   *************  *",
	"*                  *",
	"*                  *",
	"********************",

};

bool IsWall(int x, int y)
{
	if (map_text[y][x] == '*')
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
	ground.init("asset/model/ground.x");
	ground.set({ 0,-1,0 }, { 0,0,0 }, {1,1,1});

	wall.init("asset/model/sample.x");
}

void DrawMap()
{
	ground.draw();

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (IsWall(i, j))
			{
				wall.set({ (float)i - 9.5f ,1, (float)j - 9.5f }, { 0,0,0 }, { 1,1,1 });
				wall.draw();
			}

		}
	}
}