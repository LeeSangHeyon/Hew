#include <d3dx9.h>
#include<math.h>
#include"common.h"

bool CollisionPoint(D3DXVECTOR3 p1, D3DXVECTOR3 p2, float radius)
{
	float distance = hypot(fabsf(p1.x - p2.x), fabsf(p1.z - p2.z));

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