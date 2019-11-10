#pragma once

#include <d3dx9.h>
#include "mydirect3d.h"
#include "Myxinput.h"



class PLAYER
{

private:

	LPDIRECT3DVERTEXBUFFER9	pD3DVtxBuff;		//���_�o�b�t�@
	D3DXMATRIX mtxWorld;				//���[���h�}�g���b�N�X
	D3DXMATRIX mtxScl;		//�X�P�[�����O�s��
	D3DXMATRIX mtxRot;		//��]�s��
	D3DXMATRIX mtxTrs;		//���s�ړ��s��

protected:

	D3DXVECTOR3 scl;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;


public:

	float speed = 1.8f;


	PLAYER();

	void Init();

	void Draw();

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