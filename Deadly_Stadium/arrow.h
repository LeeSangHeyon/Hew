#pragma once
#include <d3dx9.h>
#include "mydirect3d.h"
#include "Myxinput.h"


class ARROW
{

private:
	D3DXVECTOR3 scl;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 oldpos;
	D3DXVECTOR3 rot;
	bool bUsed;

public:

	float speed = 18;

	ARROW();

	void Init();

	void Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	void Destroy();

	void Update();

	void Draw();

	void OutCheck();

	void WallCheck();

	bool isUsed();

};