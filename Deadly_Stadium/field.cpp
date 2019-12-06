#include <d3dx9.h>
#include <math.h>
#include "mydirect3d.h"
#include "texture.h"
#include "common.h"
#include "debug_printf.h"
#include "sprite.h"


//�w�i�o�b�t�@

LPDIRECT3DVERTEXBUFFER9	g_FieldVtxBuff;		//���_�o�b�t�@
LPDIRECT3DINDEXBUFFER9	g_FieldIdxBuff;		//�C���f�b�N�X�o�b�t�@

D3DXMATRIX		g_mtxFWorld;				//���[���h�}�g���b�N�X

int				g_pNum;

/*------------------------------------------------------------------------------
   �֐���`
------------------------------------------------------------------------------*/

void Field_Initialize(float tw, float th, int fx, int fy)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	//�w�i


	int Ground_N = (fx + 1) * (fy + 1);

	int stripN = 2 * (fx + 2) * fy - 2;

	g_pNum = 2 * (fx + 2) * fy - 4;

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * Ground_N,		//���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,		//���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_3D,			//�g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,		//���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_FieldVtxBuff,			//���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL);

	//���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_3D *GVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_FieldVtxBuff->Lock(0, 0, (void**)&GVtx, 0);

	//���_���W�̐ݒ�
	float mid_x = fx / 2;
	float mid_y = fy / 2;

	for (int i = 0; i < fy + 1; i++)
	{
		for (int j = 0; j < fx + 1; j++)
		{
			GVtx[i * (fx + 1) + j].vtx = D3DXVECTOR3((j - mid_x) * tw, 0, (i - mid_y) * th);
		}
	}


	//�@���x�N�g���̐ݒ�
	for (int i = 0; i < Ground_N; i++)
	{
		GVtx[i].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	}


	//���ˌ��̐ݒ�
	for (int i = 0; i < Ground_N; i++)
	{
		GVtx[i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	}

	//�e�N�X�`�����W�̐ݒ�
	for (int i = 0; i < fy + 1; i++)
	{
		for (int j = 0; j < fx + 1; j++)
		{
			int Tx = 0, Ty = 0;
			if (j % 2)
				Tx = 1;
			if (i % 2)
				Ty = 1;
			GVtx[i * (fx + 1) + j].tex = D3DXVECTOR2(Tx, Ty);
		}

	}



	//���_�f�[�^���A�����b�N����
	g_FieldVtxBuff->Unlock();


	//�C���f�b�N�X�o�b�t�@������
	pDevice->CreateIndexBuffer(sizeof(WORD) * stripN,		//���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,		//���_�o�b�t�@�̎g�p�@
		D3DFMT_INDEX16,			//�g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,		//���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_FieldIdxBuff,			//���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL);

	//�C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�
	WORD*	GIdx;

	g_FieldIdxBuff->Lock(0, 0, (void**)&GIdx, 0);

	for (int i = 0; i < fy; i++)
	{
		if (i > 0)
		{
			//JUMP
			GIdx[(i * (fx + 2)) * 2 - 2] = i * (fx + 1) + fx;
			GIdx[(i * (fx + 2)) * 2 - 1] = i * (fx + 1);
		}
		//STRIP
		for (int j = 0; j < fx + 1; j++)
		{
			GIdx[(i * (fx + 2) + j) * 2 + 0] = (i + 0) * (fx + 1) + j;
			GIdx[(i * (fx + 2) + j) * 2 + 1] = (i + 1) * (fx + 1) + j;
		}

	}

	g_FieldIdxBuff->Unlock();
}

void Field_Draw()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice) return;

	D3DXVECTOR3 scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 pos = D3DXVECTOR3(0, -0.5f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0, 0, 0);

	D3DXMATRIX mtxScl;		//�X�P�[�����O�s��
	D3DXMATRIX mtxRot;		//��]�s��
	D3DXMATRIX mtxTrs;		//���s�ړ��s��

	//g_pos = D3DXVECTOR3(sin(D3DXToRadian(g_Rotation * 100)), cos(D3DXToRadian(g_Rotation * 100)), cos(D3DXToRadian(g_Rotation * 100)));

	D3DXMatrixIdentity(&g_mtxFWorld);	//���[���h�s���P�ʍs��ɏ�����

	//���]		���[���h�s�� = �X�P�[�����O�s�� * ��]�s�� * ���s�ړ��s��
	//���]		���[���h�s�� = �X�P�[�����O�s�� * ���s�ړ��s�� * ��]�s��

	//�X�P�[���s����쐬&���[���h�s��֍���
	D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&g_mtxFWorld, &g_mtxFWorld, &mtxScl);


	//��]�s����쐬&���[���h�s��֍���
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&g_mtxFWorld, &g_mtxFWorld, &mtxRot);

	//���s�ړ��s����쐬&���[���h�s��֍���
	D3DXMatrixTranslation(&mtxTrs, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&g_mtxFWorld, &g_mtxFWorld, &mtxTrs);

	//���[���h�}�g���b�N�X��ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxFWorld);

	//�`�悵�����|���S���̒��_�o�b�t�@���f�[�^�X�g���[���ɃZ�b�g
	pDevice->SetStreamSource(0, g_FieldVtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetIndices(g_FieldIdxBuff);

	//�`�悵�����|���S���̒��_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_FIELD));
	//pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 12);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		0,
		0,
		g_pNum);

	//g_pos = D3DXVECTOR3(sin(D3DXToRadian(g_Rotation * 100)), cos(D3DXToRadian(g_Rotation * 100)), cos(D3DXToRadian(g_Rotation * 100)));

	D3DXMatrixIdentity(&g_mtxFWorld);	//���[���h�s���P�ʍs��ɏ�����

	//���]		���[���h�s�� = �X�P�[�����O�s�� * ��]�s�� * ���s�ړ��s��
	//���]		���[���h�s�� = �X�P�[�����O�s�� * ���s�ړ��s�� * ��]�s��

	//�X�P�[���s����쐬&���[���h�s��֍���
	D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&g_mtxFWorld, &g_mtxFWorld, &mtxScl);


	//��]�s����쐬&���[���h�s��֍���
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&g_mtxFWorld, &g_mtxFWorld, &mtxRot);

	//���s�ړ��s����쐬&���[���h�s��֍���
	D3DXMatrixTranslation(&mtxTrs, pos.x, pos.y + 0.02, pos.z - 13);
	D3DXMatrixMultiply(&g_mtxFWorld, &g_mtxFWorld, &mtxTrs);

	//���[���h�}�g���b�N�X��ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxFWorld);

	//�`�悵�����|���S���̒��_�o�b�t�@���f�[�^�X�g���[���ɃZ�b�g
	pDevice->SetStreamSource(0, g_FieldVtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetIndices(g_FieldIdxBuff);

	//�`�悵�����|���S���̒��_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_GRAY));
	//pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 12);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		0,
		0,
		g_pNum);

}