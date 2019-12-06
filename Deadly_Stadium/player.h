#pragma once

#include <d3dx9.h>
#include "mydirect3d.h"
#include "Myxinput.h"

#define	MAX_ARROW	(128)

typedef struct PLAYER_STATUS
{
	int HP;
	int reg_HP;
	int SP;
	int LVL;
	int EXP;
	int ATK;

	bool bSkill;
};

class PLAYER
{

protected:

	D3DXVECTOR3 scl;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 oldpos;
	D3DXVECTOR3 rot;

	PLAYER_STATUS status;

public:

	float speed = 1.8f;

	PLAYER();

	void BorderCheck(float abx, float abz);

	void WallCheck();

	D3DXVECTOR3 GetPos() { return pos; }

	PLAYER_STATUS GetStatus() { return status; }

	void EXP_UP(int exp);

	void SP_UP(int sp);

	void DAMAGE(int dmg);
};

class PLAYER_A : public PLAYER
{
private:
	bool bAiming;

public:

	PLAYER_A();

	void Init();

	void Draw();

	void Update(GAMEPAD pad);

};

class PLAYER_B : public PLAYER
{
private:

public:

	PLAYER_B();

	void Init();

	void Draw();

	void Update(GAMEPAD pad);

	void HitCheck();

};