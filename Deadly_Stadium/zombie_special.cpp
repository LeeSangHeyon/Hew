#include "zombie_special.h"
#include "model.h"
#include "collider.h"
#include "arrow.h"
#include "game.h"

#define HAMMER_NUMBER (20)
#define HAMMER_Y_LIMITE (5) 
#define HAMMER_Y_FALLING (7)

#define MAX_ARROW_ZOMBIE (10)

ARROW arrow_zombie[MAX_ARROW_ZOMBIE];

//////////////////////////////////////////////////
//BASEBALL ZOMBIE
/////////////////////////////////////////////////

//遠距離プレイヤーにターゲットをセットする
void ZOMBIE_BASEBALL::BASEBALL_AI::SetTargetPlayer()
{
	TargetPos = GetPlayerA()->GetPos();
}

//プレイヤーについて行く
void ZOMBIE_BASEBALL::BASEBALL_AI::FollowTarget()
{
	SetTargetPlayer();
	
	float xDistance = TargetPos.x - pos.x;
	float zDistance = TargetPos.z - pos.z;
	float hypotenuse = sqrt((xDistance * xDistance) + (zDistance * zDistance));

	//プレイヤーを追う
	pos.x += (xDistance / hypotenuse) * speed;
	pos.z += (zDistance / hypotenuse) * speed;

	//プレイヤーを向く処理
	rot = RotationFromPos(pos, TargetPos);
}


//ゾンビにプレイヤーがあると攻撃する
void ZOMBIE_BASEBALL::BASEBALL_AI::Attack()
{
	if (CollisionBox(TargetPos, pos, 0.2f))
	{
		//FIXME
		//PLAYER GET DAMAGE
	}
}

void ZOMBIE_BASEBALL::Init(D3DXVECTOR3 _pos, D3DXVECTOR3 _rot, D3DXVECTOR3 _scl)
{
	AI.pZombie = this;
	bUsed = false;
	pos = _pos;
	rot = _rot;
	scl = _scl;
	MoveSpeed = 3.0f;
}

void ZOMBIE_BASEBALL::Update()
{
	if (bUsed)
	{
		AI.pos = pos;
		AI.rot = rot;
		AI.FollowTarget();
		pos = AI.pos;
		rot = AI.rot;

		if (HP <= 0)
			bUsed = false;

		for (int i = 0; i < MAX_ARROW_ZOMBIE; i++)
		{
			arrow_zombie[i].Update();
			AI.Attack();
		}
	}
}

void ZOMBIE_BASEBALL::Draw()
{
	if (bUsed)
	{
		Model_Render(MODEL_ZOMBIE,pos,rot);

		for (int i = 0; i < MAX_ARROW_ZOMBIE; i++)
		{
			arrow_zombie[i].Draw();
		}
	}
}

void ZOMBIE_BASEBALL::GetDamage(int Damage)
{
	HP -= Damage;
}

void  ZOMBIE_BASEBALL::CreatZombie(D3DXVECTOR3 _pos)
{
	bUsed = true;
	bAttack = true;
	pos = _pos;
	MoveSpeed = 3.0f;
	HP = 120;
}

//ゾンビにRrojectile来ると反射する
void ZOMBIE_BASEBALL::BASEBALL_AI::ReflectRrojectile()
{
	if (pZombie->ReflectOn)
	{
		//FIXME
		//ReflectRrojectile
		for (int i = 0; i < MAX_ARROW_ZOMBIE; i++)
		{
			if (!arrow_zombie[i].isUsed())
			{
				float ran = rand() % 90;

				if (ran <= 45)
				{
					ran *= -1;
				}
				else
				{
					ran *= 1;
				}

				D3DXVECTOR3 a = pZombie->rot;
				a.y += D3DXToRadian(ran);
				//ゾンビの1ラジアン範囲内でランダムで反射するように
				arrow_zombie[i].Create(false, pZombie->ATK, pZombie->pos, a);
				break;
			}
		}

		pZombie->ReflectOn = false;
	}
}


//////////////////////////////////////////////////
//HAMMER
//////////////////////////////////////////////////
HAMMER hammer[HAMMER_NUMBER];

HAMMER::HAMMER()
{

}

HAMMER::~HAMMER()
{

}

void HAMMER::Init_Hammer()
{
	pPlayer = nullptr;
	D3DXVECTOR3 pos = D3DXVECTOR3(-2, 0, 2);
	D3DXVECTOR3 rot = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 TrowTargetPos = D3DXVECTOR3(0, 0, 0);
	TrowSpeed = 0.1f;
	StopDraw = true;
	DisappearFlag = false;
	IsUsed = false;
	bAttack = true;
	sibal = false;
	BeforeLandCnt = 0;
}

//ゾンビにこのHAMMERをセットする
void HAMMER::Setting(PLAYER* Target , D3DXVECTOR3 ZombiePos)
{
	IsUsed = true;
	StopDraw = false;
	pPlayer = Target;
	pos = ZombiePos;
}

//プレイヤーの方向で飛ぶが、一定の高さになれば姿を消す
void HAMMER::Throwing()
{
	if (IsTrowed)
	{
		if (!sibal)
		{
			if (pos.y <= HAMMER_Y_LIMITE)
			{
				float xDistance = TrowTargetPos.x - pos.x;
				float zDistance = TrowTargetPos.z - pos.z;
				float hypotenuse = sqrt((xDistance * xDistance) + (zDistance * zDistance));

				//プレイヤーを追う
				pos.x += (xDistance / hypotenuse) * TrowSpeed;
				pos.z += (zDistance / hypotenuse) * TrowSpeed;
				pos.y += TrowSpeed * 2;
			}
			else
			{
				sibal = true;
				IsTrowed = false;
				StopDraw = true;
			}
		}

	}
}
//姿を消した後、落ちる
void HAMMER::Landing()
{

	//SETTING
	if (StopDraw && !IsTrowed)
	{
		StopDraw = false;
		IsLanded = true;
		pos = pPlayer->GetPos();
		pos.y = HAMMER_Y_FALLING;
	}

	//FALL
	if (IsLanded)
	{
		BeforeLandCnt++;
		if (BeforeLandCnt > 30)
		{
			if (pos.y >= -1)
			{
				pos.y -= 0.1f;
				DrawShadowLandinSpot();
			}
			else
			{
				GiveDamage();
				StopDraw = true;
				IsLanded = false;
				DisappearFlag = true;
			}
		}

	}
}

//FIXEME!!
//MADEME!!
//落ちる時、地面が近ければ近いほど影を大きく描く
void HAMMER::DrawShadowLandinSpot()
{

}

//FIXEME!!
//MADEME!!
//範囲内のプレイヤーにダメージを与える
void HAMMER::GiveDamage()
{
	if (bAttack)
	{
		if (CollisionPoint(GetPlayerA()->GetPos(), pos, 1.0f))
		{
			GetPlayerA()->DAMAGE(10);
			bAttack = false;
		}

		if (CollisionPoint(GetPlayerB()->GetPos(), pos, 1.0f))
		{
			GetPlayerB()->DAMAGE(10);
			bAttack = false;
		}
	}
}

//落ちた後、どんどん薄くなって消える
void HAMMER::Disappear()
{
	if (DisappearFlag)
	{
		Init_Hammer();
	}
}
	


//////////////////////////////////////////////////
//HAMMER ZOMBIE AI
/////////////////////////////////////////////////
ZOMBIE_HAMMER::HAMMER_AI::HAMMER_AI()
{
	for (int i = 0; i < HAMMER_NUMBER; i++)
	{
		if (!hammer[i].IsUsed)
		{
			pHammer = &hammer[i];
			//Maybe Error
			pHammer->Setting(pPlayer , D3DXVECTOR3(0,0,0));
			break;
		}
	}
}

void ZOMBIE_HAMMER::HAMMER_AI::AI_Draw()
{
}

void ZOMBIE_HAMMER::HAMMER_AI::AI_Update()
{
	SetTargetPlayer();
	Charge();
	LookAtPlayerBeforeShot();
	Reload();
}

//FIXME
//今はそのまま座標をぶち込んでいるが、ベター版にはローカル座標を調べて適応すること
//投げる前にHammerを持つ
void ZOMBIE_HAMMER::HAMMER_AI::GetHammer()
{
	//FIXME!!
		/*pHammer->pos = pZombie->pos;
		pHammer->rot = pZombie->rot;*/

}
//FIXME!!
//4つプレイヤー中でターゲットをセットする
void ZOMBIE_HAMMER::HAMMER_AI::SetTargetPlayer()
{
	if(GetPlayerAPos() == WhichIsCloser(pZombie->pos, GetPlayerAPos(), GetPlayerBPos()))
		pPlayer = GetPlayerB();
	else
		pPlayer = GetPlayerA();
	TargetPos = pPlayer->GetPos();
}

//FIXME!!
//ターゲットになったプレイヤーが死んだら
//他のプレイヤーをターゲットにする
void ZOMBIE_HAMMER::HAMMER_AI::ReSearchPlayer()
{
	//プレイヤーの死亡の時
	if (true)
	{
		SetTargetPlayer();
	}
}

//FIXME!!
//ターゲットが決まったら回す
void ZOMBIE_HAMMER::HAMMER_AI::Charge()
{
	if (ChargeFlag)
	{
		pZombie->rot.y += 0.1f;
		if (pZombie->rot.y >= D3DXToRadian(360))
		{
			pZombie->rot.y -= D3DXToRadian(360);
		}
		GetHammer();
		if (!ShotFlag)
		{
			if (ChargeTimeCnt <= 0)
			{
				ChargeTimeCnt = ChargeTime;
				ShotFlag = true;
				ChargeFlag = false;
			}
			else
			{
				ChargeTimeCnt -= 0.1;
			}
		}
	}
}
//Chargeが完了したらプレイヤーに向かう
void ZOMBIE_HAMMER::HAMMER_AI::LookAtPlayerBeforeShot()
{
	if (ShotFlag)
	{
		D3DXVECTOR3 y = RotationFromPos(pZombie->pos, TargetPos);
		//FIXME
		//回ってる角度がプレイヤーに向いたら
		if (true)
		{
			ChargeFlag = false;
			ShotFlag = false;
			Shot();
		}
	}
}

//FIXME!!
//Chargeが完了したら上に向かって放つ
void ZOMBIE_HAMMER::HAMMER_AI::Shot()
{
	pHammer->TrowTargetPos = pPlayer->GetPos();
	pHammer->IsTrowed = true;
	IsReload = true;
	pHammer = nullptr;
	for (int i = 0; i < HAMMER_NUMBER; i++)
	{
		if (!hammer[i].IsUsed)
		{
			pHammer = &hammer[i];
			pHammer->Setting(pPlayer , pZombie->pos);
			break;
		}
	}
}

//発射後、一定時間がすぎたらReloadする
void ZOMBIE_HAMMER::HAMMER_AI::Reload()
{
	if (IsReload)
	{


		if (ReloadTimeCnt <= 0)
		{

			ReloadTimeCnt = ReloadTime;
			IsReload = false;
			ChargeFlag = true;
		}
		else
		{
			ReloadTimeCnt -= 0.1;
		}
	}
}

//////////////////////////////////////////////////
//HAMMER ZOMBIE
/////////////////////////////////////////////////

void ZOMBIE_HAMMER::Init(D3DXVECTOR3 _pos, D3DXVECTOR3 _rot, D3DXVECTOR3 _scl)
{
	pos = _pos;
	rot = _rot;
	scl = _scl;
	AI.pZombie = this;
	MoveSpeed = 3.0f;
	HP = 100;
	bUsed = false;
}

void ZOMBIE_HAMMER::Update()
{
	//FIXME
	if (bUsed)
	{
		AI.AI_Update();
		if (HP <= 0)
			bUsed = false;
	}
}

void ZOMBIE_HAMMER::Draw()
{
	//FIXME
	if (bUsed)
	{
		Model_Render(MODEL_ZOMBIE, pos, rot);
	}

}

void ZOMBIE_HAMMER::GetDamage(int Damage)
{
	HP -= Damage;
}

void  ZOMBIE_HAMMER::CreatZombie(D3DXVECTOR3 _pos)
{
	AI.pZombie = this;
	bUsed = true;
	bAttack = true;
	pos = _pos;
	MoveSpeed = 3.0f;
	HP = 5;
}


void Init_Hammer()
{
	for (int i = 0; i < HAMMER_NUMBER; i++)
	{
		hammer[i].Init_Hammer();
	}
}

void Update_Hammer()
{
	for (int i = 0; i < HAMMER_NUMBER; i++)
	{
		if (hammer[i].IsUsed)
		{
			hammer[i].Throwing();
			hammer[i].Landing();
			hammer[i].Disappear();
		}
	}

}

void Draw_Hammer()
{
	for (int i = 0; i < HAMMER_NUMBER; i++)
	{
		if (hammer[i].IsUsed && !hammer[i].StopDraw)
		{
			Model_Render(MODEL_WALL, hammer[i].pos, hammer[i].rot);
		}
	}
}