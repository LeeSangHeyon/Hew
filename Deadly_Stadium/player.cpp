#include <d3dx9.h>
#include <math.h>
#include "mydirect3d.h"
#include "texture.h"
#include "sprite.h"
#include "common.h"
#include "input.h"
#include "Myxinput.h"
#include "camera.h"
#include "player.h"

PLAYER::PLAYER()
{
	pos = D3DXVECTOR3(0.0f, 0.2f, 0.0f);
	rot = D3DXVECTOR3(0, 0, 0);
	scl = D3DXVECTOR3(0.08f, 0.32f, 0.06f);

}


void PLAYER::Init()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	//�I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 36,		//���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,		//���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_3D,			//�g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,		//���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&pD3DVtxBuff,			//���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL);

	//���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�

	D3DXVECTOR3 Cube[8] =
	{
		D3DXVECTOR3(-0.5f,-0.5f,  0.5f),	//0
		D3DXVECTOR3(0.5f,-0.5f,  0.5f),		//1
		D3DXVECTOR3(-0.5f, 0.5f,  0.5f),	//2
		D3DXVECTOR3(0.5f, 0.5f,  0.5f),		//3
		D3DXVECTOR3(0.5f, 0.5f, -0.5f),		//4
		D3DXVECTOR3(0.5f,-0.5f, -0.5f),		//5
		D3DXVECTOR3(-0.5f,-0.5f, -0.5f),	//6
		D3DXVECTOR3(-0.5f, 0.5f, -0.5f)		//7
	};

	pVtx[0].vtx = pVtx[19].vtx = pVtx[21].vtx = pVtx[26].vtx = pVtx[29].vtx = Cube[0];
	pVtx[1].vtx = pVtx[3].vtx = pVtx[6].vtx = pVtx[28].vtx = Cube[1];
	pVtx[2].vtx = pVtx[5].vtx = pVtx[22].vtx = pVtx[30].vtx = Cube[2];
	pVtx[4].vtx = pVtx[8].vtx = pVtx[11].vtx = pVtx[31].vtx = pVtx[33].vtx = Cube[3];
	pVtx[10].vtx = pVtx[14].vtx = pVtx[17].vtx = pVtx[34].vtx = Cube[4];
	pVtx[7].vtx = pVtx[9].vtx = pVtx[12].vtx = pVtx[25].vtx = pVtx[27].vtx = Cube[5];
	pVtx[13].vtx = pVtx[15].vtx = pVtx[18].vtx = pVtx[24].vtx = Cube[6];
	pVtx[16].vtx = pVtx[20].vtx = pVtx[23].vtx = pVtx[32].vtx = pVtx[35].vtx = Cube[7];


	//�@���x�N�g���̐ݒ�
	for (int i = 0; i < 6; i++)
	{
		pVtx[0 + 6 * i].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1 + 6 * i].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2 + 6 * i].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3 + 6 * i].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[4 + 6 * i].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[5 + 6 * i].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	}


	//���ˌ��̐ݒ�
	for (int i = 0; i < 6; i++)
	{
		pVtx[0 + 6 * i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1 + 6 * i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2 + 6 * i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3 + 6 * i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[4 + 6 * i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5 + 6 * i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//�e�N�X�`�����W�̐ݒ�
	for (int i = 0; i < 6; i++)
	{
		pVtx[0 + 6 * i].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1 + 6 * i].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2 + 6 * i].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[3 + 6 * i].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[4 + 6 * i].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[5 + 6 * i].tex = D3DXVECTOR2(0.0f, 0.0f);
	}

	//���_�f�[�^���A�����b�N����
	pD3DVtxBuff->Unlock();

}


void PLAYER::Draw()
{

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice) return;

	D3DXMatrixIdentity(&mtxWorld);	//���[���h�s���P�ʍs��ɏ�����


	//�X�P�[���s����쐬&���[���h�s��֍���
	D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	//��]�s����쐬&���[���h�s��֍���
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	//���s�ړ��s����쐬&���[���h�s��֍���
	D3DXMatrixTranslation(&mtxTrs, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrs);


	//���[���h�}�g���b�N�X��ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//�`�悵�����|���S���̒��_�o�b�t�@���f�[�^�X�g���[���ɃZ�b�g
	pDevice->SetStreamSource(0, pD3DVtxBuff, 0, sizeof(VERTEX_3D));

	//�`�悵�����|���S���̒��_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�|���S���̕`��
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_KIZUNA));
	pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 12);

}


D3DXVECTOR3 PLAYER::GetPos()
{
	return pos;
}


PLAYER_A::PLAYER_A()
{
	pos = D3DXVECTOR3(-0.5f, 0.4f, 0.0f);
	rot = D3DXVECTOR3(0, 0, 0);
	scl = D3DXVECTOR3(0.3f, 0.8f, 0.2f);
}

void PLAYER_A::Update(GAMEPAD pad)
{

	if (Keyboard_IsPress(DIK_W))
	{
		pos.z += speed / 60.0f;
	}
	if (Keyboard_IsPress(DIK_S))
	{
		pos.z -= speed / 60.0f;
	}
	if (Keyboard_IsPress(DIK_D))
	{
		pos.x += speed / 60.0f;
	}
	if (Keyboard_IsPress(DIK_A))
	{
		pos.x -= speed / 60.0f;
	}

	//���X�e�B�b�N�̎擾
	Stick Lstick = pad.GetLeftStick();

	if (Lstick.x || Lstick.y)
	{
		pos.x += Lstick.x / hypotf(Lstick.x, Lstick.y) * speed / 60.0f;
		pos.z += Lstick.y / hypotf(Lstick.x, Lstick.y) * speed / 60.0f;
	}

	//�E�X�e�B�b�N�̎擾
	Stick Rstick = pad.GetRightStick();

	if (Rstick.x || Rstick.y)
	{
		rot.y = (Rstick.y > 0) ? asinf(Rstick.x / hypotf(Rstick.x, Rstick.y)) : -asinf(Rstick.x / hypotf(Rstick.x, Rstick.y));
	}

}

PLAYER_B::PLAYER_B()
{
	pos = D3DXVECTOR3(0.5f, 0.4f, 0.0f);
	rot = D3DXVECTOR3(0, 0, 0);
	scl = D3DXVECTOR3(0.3f, 0.8f, 0.2f);
}

void PLAYER_B::Update(GAMEPAD pad)
{

	if (Keyboard_IsPress(DIK_UP))
	{
		pos.z += speed / 60.0f;
	}
	if (Keyboard_IsPress(DIK_DOWN))
	{
		pos.z -= speed / 60.0f;
	}
	if (Keyboard_IsPress(DIK_RIGHT))
	{
		pos.x += speed / 60.0f;
	}
	if (Keyboard_IsPress(DIK_LEFT))
	{
		pos.x -= speed / 60.0f;
	}

	//���X�e�B�b�N�̎擾
	Stick Lstick = pad.GetLeftStick();
	if (Lstick.x || Lstick.y)
	{
		pos.x += Lstick.x / hypotf(Lstick.x, Lstick.y) * speed / 60.0f;
		pos.z += Lstick.y / hypotf(Lstick.x, Lstick.y) * speed / 60.0f;
	}

	//�E�X�e�B�b�N�̎擾
	Stick Rstick = pad.GetRightStick();

	if (Rstick.x || Rstick.y)
	{
		rot.y = (Rstick.y > 0) ? asinf(Rstick.x / hypotf(Rstick.x, Rstick.y)) : -asinf(Rstick.x / hypotf(Rstick.x, Rstick.y));
	}

}