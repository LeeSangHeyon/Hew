#pragma once

#include <d3dx9.h>
#include "mydirect3d.h"
#include "Myxinput.h"

#define	MAX_ARROW	(64)

class PLAYER
{

protected:

	D3DXVECTOR3 scl;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 oldpos;
	D3DXVECTOR3 rot;


public:

	float speed = 1.8f;

	PLAYER();

	void Init();

	void Draw();

	void BorderCheck(float abx, float abz);

	void WallCheck();

	D3DXVECTOR3 GetPos();

};

class PLAYER_A : public PLAYER
{
public:

	PLAYER_A();

	void Update(GAMEPAD pad);

};

class PLAYER_B : public PLAYER
{
public:

	PLAYER_B();

	void Update(GAMEPAD pad);

};