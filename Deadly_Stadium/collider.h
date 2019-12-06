#pragma once

#include <d3dx9.h>

bool CollisionPoint(D3DXVECTOR3 p1, D3DXVECTOR3 p2, float radius);
bool CollisionBox(D3DXVECTOR3 p, D3DXVECTOR3 box, float radius);
D3DXVECTOR3 RotationFromPos(D3DXVECTOR3 my, D3DXVECTOR3 at);
D3DXVECTOR3 WhichIsCloser(D3DXVECTOR3 my, D3DXVECTOR3 p1, D3DXVECTOR3 p2);