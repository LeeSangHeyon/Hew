#include <d3dx9.h>
#include "helicopter.h"
#include "model.h"
//XFile Dom_model;
D3DXVECTOR3 motterRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 10.0f, 3.0f);
D3DXVECTOR3 rot = D3DXVECTOR3(0, 0, 0);
D3DXVECTOR3 scl = D3DXVECTOR3(10.0f, 10.0f, 10.0f);

//FIXME!!
//false‚É‚µ‚ë
bool bHeliUse = false;
void InitHeli()
{

}

void UpdateHeli()
{
	if (bHeliUse)
	{
		if (pos.y <= 1)
		{
			
		}
		else
		{
			pos.y -= 0.05f;
		}
		motterRot.y += 0.15f;

	}
}

void DrawHeli()
{
	if (bHeliUse)
	{
		Model_Render(MODEL_HELI, pos, rot);
		Model_Render(MODEL_HELIMOTTER, pos, motterRot);
	}

}

void LastScene()
{

}

void SetHeli()
{
	bHeliUse = true;
}
