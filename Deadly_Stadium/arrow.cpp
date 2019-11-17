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
#include "map.h"
#include "xfile.h"


XFile arrow_model;

ARROW::ARROW()
{
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rot = D3DXVECTOR3(0, 0, 0);
	scl = D3DXVECTOR3(0.1f, 0.05f, 0.8f);
	bUsed = false;

}

void ARROW::Init()
{
	arrow_model.init("asset/model/sample.x");
}


void ARROW::Create(D3DXVECTOR3 p, D3DXVECTOR3 r)
{
	pos = p;
	rot = r;
	bUsed = true;
}

void ARROW::Update()
{
	if (bUsed)
	{
		oldpos = pos;
		pos.x += sin(rot.y) * speed / 60.0f;
		pos.z += cos(rot.y) * speed / 60.0f;

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
	arrow_model.set(pos, rot, scl);
	arrow_model.draw();

}

void ARROW::OutCheck()
{
	float distance = hypotf(GetCamera().GetPos().x - pos.x, GetCamera().GetPos().z - pos.z);
	if (distance > 8.0f)
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

bool ARROW::isUsed()
{
	return bUsed;
}