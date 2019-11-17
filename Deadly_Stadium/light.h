#pragma once

#include <d3dx9.h>
#include "mydirect3d.h"

class CLight {
public:
	static void Init();
	static void Uninit();
	static void Set(bool bStatus);
	static D3DXVECTOR3 GetDir();
	static D3DLIGHT9 GetLight();
};