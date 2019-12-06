#pragma once
#include <d3dx9.h>
#include "player.h"
#include "mydirect3d.h"
#include "zombie.h"

void Init_Hammer();
void Update_Hammer();
void Draw_Hammer();
//FIXME!!
//////////////////////////////////////////////////
//BASEBALL ZOMBIE CLASS
/////////////////////////////////////////////////
class ZOMBIE_BASEBALL: public ZOMBIE
{
private:
	class BASEBALL_AI
	{
	public:
		D3DXVECTOR3 rot;
		D3DXVECTOR3 pos;
		ZOMBIE_BASEBALL* pZombie;
		D3DXVECTOR3 TargetPos;

	public:
		void SetTargetPlayer();
		void ReSearchPlayer();
		void FollowTarget();
		void ReflectRrojectile();
		void Attack();

	protected:
		float speed = 0.01f;
	};
public:
	bool ReflectOn = false;
	BASEBALL_AI AI;
	void CreatZombie(D3DXVECTOR3 _pos);
	void Init(
		D3DXVECTOR3 _pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f),
		D3DXVECTOR3 _rot = D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3 scl = D3DXVECTOR3(0.1f, 0.1f, 0.1f));
	void Draw();
	void Update();
	void GetDamage(int Damage);
};
/////////////////////////////////////////////////
//HAMMER CLASS
/////////////////////////////////////////////////
class HAMMER
{
public:
	HAMMER();
	~HAMMER();
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 TrowTargetPos;
	PLAYER* pPlayer;
	float TrowSpeed = 0.1f;
	int BeforeLandCnt = 0;
	bool StopDraw = false;
	bool DisappearFlag;
	bool IsUsed = false;
	bool bAttack = true;
	bool sibal;
	bool IsTrowed;
	bool IsCameraOut;
	bool IsLanded;

	void Init_Hammer();
	void Setting(PLAYER* Target , D3DXVECTOR3 ParentZombiePos);
	void Throwing();
	void Landing();
	void DrawShadowLandinSpot();
	void Disappear();
	void GiveDamage();


private:

};

//FIXME!!
//////////////////////////////////////////////////
//HAMMER ZOMBIE CLASS
/////////////////////////////////////////////////
class ZOMBIE_HAMMER : public ZOMBIE
{
private:

	class HAMMER_AI
	{

	public:
		ZOMBIE_HAMMER* pZombie;
		PLAYER* pPlayer;
		HAMMER* pHammer;
		D3DXVECTOR3 TargetPos;
		float Roation_test;
	public:
		HAMMER_AI();
		void AI_Draw();
		void AI_Update();
		void GetHammer();
		void SetTargetPlayer();
		void ReSearchPlayer();
		void Charge();
		void LookAtPlayerBeforeShot();
		void Shot();
		void Reload();
	private:
		
		//FIXME
		//ちゃんとinitとコンストラクタに書くこと
	protected:
		bool IsReload = false;
		bool ChargeFlag = true;
		bool ShotFlag = false;
		float speed = 0.02f;
		float ChargeTime = 5;
		float ChargeTimeCnt = 5;
		float ReloadTime = 20;
		float ReloadTimeCnt = 20;
	};
public:
	HAMMER_AI AI;
	void CreatZombie(D3DXVECTOR3 _pos);
	void Init(
		D3DXVECTOR3 _pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f),
		D3DXVECTOR3 _rot = D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3 scl = D3DXVECTOR3(0.1f, 0.1f, 0.1f));
	void Draw();
	void Update();
	void GetDamage(int Damage);
};