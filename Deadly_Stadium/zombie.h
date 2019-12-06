#pragma once
#include <d3dx9.h>
#include "mydirect3d.h"
#include "game.h"
#include "player.h"

class ZOMBIE
{

private:

protected:
	D3DXVECTOR3 scl;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 oldpos;
	D3DXVECTOR3 rot;

public:
	ZOMBIE();
	int HP;
	int ATK;
	int MoveSpeed;
	bool bAttack;

	bool bUsed;
	D3DXVECTOR3 GetPos();


	void TakeDamage(int Damage);

};

class ZOMBIE_BASIC : public ZOMBIE
{

private:
	class ZOMBIEAI
	{
	private:
		D3DXVECTOR3 rot;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 targetPos;

	public:
		ZOMBIEAI();
		void SetPosRot(D3DXVECTOR3 pos,D3DXVECTOR3 rot);
		D3DXVECTOR3 GetPos() { return pos; }
		D3DXVECTOR3 GetRot() { return rot; }
		D3DXVECTOR3 GetTargetPos() { return targetPos; }
		void SetTargetPlayer();
		void FollowTarget();
		

	protected:
		float speed = 0.02f;

	};

public:

	ZOMBIEAI AI;
	void SetPosRot(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Init(
		D3DXVECTOR3 _pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f) ,
		D3DXVECTOR3 _rot = D3DXVECTOR3(0, 0, 0) ,
		D3DXVECTOR3 scl = D3DXVECTOR3(30.1f, 30.1f, 30.1f));
	void Draw();
	void Update();
	void Attack();
	void CreatZombie(D3DXVECTOR3 _pos);
};

