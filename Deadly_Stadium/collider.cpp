#define _USE_MATH_DEFINES
#include <d3dx9.h>
#include<math.h>
#include"common.h"

bool CollisionPoint(D3DXVECTOR3 p1, D3DXVECTOR3 p2, float radius)
{
	float distance = hypotf(p1.x - p2.x, p1.z - p2.z);

	if (distance < radius)
		return true;
	else
		return false;
}

bool CollisionBox(D3DXVECTOR3 p, D3DXVECTOR3 box, float radius)
{
	float abx = fabsf(p.x - box.x);
	float abz = fabsf(p.z - box.z);

	if (abx < radius + 0.5f && abx < radius + 0.5f)
		return true;
	else
		return false;
}

D3DXVECTOR3 RotationFromPos(D3DXVECTOR3 my, D3DXVECTOR3 at)
{
	D3DXVECTOR3 vtx = (at - my) / hypot(my.x - at.x, my.z - at.z);
	float y = (vtx.z > 0) ? asinf(vtx.x) : M_PI + asinf(-vtx.x);
	return { 0,y,0 };
}

D3DXVECTOR3 WhichIsCloser(D3DXVECTOR3 my, D3DXVECTOR3 p1, D3DXVECTOR3 p2)
{
	float d1 = hypotf(my.x - p1.x, my.z - p1.z);
	float d2 = hypotf(my.x - p2.x, my.z - p2.z);
	if (d1 < d2)
	{
		return p1;
	}
	else
	{
		return p2;
	}
}