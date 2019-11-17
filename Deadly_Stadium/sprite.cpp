
#include <d3dx9.h>
#include <math.h>
#include "mydirect3d.h"
#include "texture.h"
#include "common.h"

#define NumGrid (20)

/*------------------------------------------------------------------------------
   �\���̐錾
------------------------------------------------------------------------------*/
// �QD�|���S�����_�\����
typedef struct Vertex2D_tag
{
    D3DXVECTOR4 position; // ���_���W�i���W�ϊ��ςݒ��_�j
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
} Vertex2D;
#define FVF_VERTEX2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1) // �QD�|���S�����_�t�H�[�}�b�g


//�J�����p�p�����[�^
D3DXVECTOR3		g_posCameraEye;			//�J�����̎��_
D3DXVECTOR3		g_posCameraAt;			//�J�����̎��_
D3DXVECTOR3		g_vecCameraUp;			//�J�����̎��_

//�v���W�F�N�V����&�J�����s��
D3DXMATRIX		g_mtxView;				//�r���[�}�g���b�N�X
D3DXMATRIX		g_mtxProjection;		//�v���W�F�N�V�����}�g���b�N�X

//�T���v���|���S���̕\�����̂Ɋւ���p�����[�^
D3DXMATRIX		g_mtxWorld;				//���[���h�}�g���b�N�X
D3DXMATRIX		g_mtxGWorld;				//���[���h�}�g���b�N�X

LPDIRECT3DVERTEXBUFFER9	g_pD3DVtxBuff;		//���_�o�b�t�@
LPDIRECT3DVERTEXBUFFER9	g_pD3DGridBuff;		//�O���b�h���_�o�b�t�@


/*------------------------------------------------------------------------------
   �O���[�o���ϐ��錾
------------------------------------------------------------------------------*/
static D3DCOLOR g_Color = 0xffffffff;
// static D3DCOLOR g_Color = D3DCOLOR_RGBA(255, 255, 255, 255);



/*------------------------------------------------------------------------------
   �֐���`
------------------------------------------------------------------------------*/

void Sprite_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	//�I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 36,		//���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,		//���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_3D,			//�g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,		//���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuff,			//���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL);

	//���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

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
		pVtx[1 + 6 * i].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2 + 6 * i].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3 + 6 * i].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[4 + 6 * i].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[5 + 6 * i].tex = D3DXVECTOR2(0.0f, 1.0f);
	}

	//���_�f�[�^���A�����b�N����
	g_pD3DVtxBuff->Unlock();

	//�O���b�h���_���W�̐ݒ�

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (NumGrid * 8 - 4),		//���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,		//���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_3D,			//�g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,		//���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DGridBuff,			//���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL);

	//���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_3D *pGrid;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pD3DGridBuff->Lock(0, 0, (void**)&pGrid, 0);

	//���_���W�̐ݒ�

	pGrid[0].vtx = D3DXVECTOR3(0.0f, 0.0f, NumGrid);
	pGrid[1].vtx = D3DXVECTOR3(0.0f, 0.0f, -NumGrid);
	pGrid[2].vtx = D3DXVECTOR3(NumGrid, 0.0f, 0.0f);
	pGrid[3].vtx = D3DXVECTOR3(-NumGrid, 0.0f, 0.0f);

	for (int i = 1; i < NumGrid; i++)
	{
		pGrid[8 * i - 4].vtx = D3DXVECTOR3(i, 0.0f, NumGrid);
		pGrid[8 * i - 3].vtx = D3DXVECTOR3(i, 0.0f, -NumGrid);
		pGrid[8 * i - 2].vtx = D3DXVECTOR3(NumGrid, 0.0f, i);
		pGrid[8 * i - 1].vtx = D3DXVECTOR3(-NumGrid, 0.0f, i);
		pGrid[8 * i + 0].vtx = D3DXVECTOR3(-i, 0.0f, NumGrid);
		pGrid[8 * i + 1].vtx = D3DXVECTOR3(-i, 0.0f, -NumGrid);
		pGrid[8 * i + 2].vtx = D3DXVECTOR3(NumGrid, 0.0f, -i);
		pGrid[8 * i + 3].vtx = D3DXVECTOR3(-NumGrid, 0.0f, -i);
	}

	for (int i = 0; i < NumGrid * 8 - 4; i++)
	{

		pGrid[i].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pGrid[i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pGrid[i].tex = D3DXVECTOR2(0.0f, 0.0f);

	}

	g_pD3DGridBuff->Unlock();
}

//�J����
void Camera_Set(void)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice) return;

	g_posCameraEye = D3DXVECTOR3(0, 4.0f, -2.0f);
	g_posCameraAt = D3DXVECTOR3(0, 0, 0);
	g_vecCameraUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�r���[�s��̍쐬
	D3DXMatrixLookAtLH(&g_mtxView,
		&g_posCameraEye,	//�J�������_
		&g_posCameraAt,		//�J���������_
		&g_vecCameraUp);	//�J���������

	//�r���[�s��̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_mtxView);


	//==============================================
	// ������ǉ��@�e�X�g�p�v���W�F�N�V�����s��̍쐬
	D3DXMatrixPerspectiveFovLH(&g_mtxProjection,
		VIEW_ANGLE,		//�r���[���ʂ̎���p
		VIEW_ASPECT,	//�r���[���ʂ̃A�X�y�N�g��
		VIEW_NEAR_Z,	//�r���[���ʂ�NearZ
		VIEW_FAR_Z);	//�r���[���ʂ�FarZ

	//�v���W�F�N�V�����s��̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_mtxProjection);

}

// �X�v���C�g�|���S���̒��_�J���[�ݒ�
void Sprite_SetColor(D3DCOLOR color)
{
	g_Color = color;
}


void Grid_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice) return;

	D3DXVECTOR3 scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 pos = D3DXVECTOR3(0, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0, 0, 0);

	D3DXMATRIX mtxScl;		//�X�P�[�����O�s��
	D3DXMATRIX mtxRot;		//��]�s��
	D3DXMATRIX mtxTrs;		//���s�ړ��s��

	//g_pos = D3DXVECTOR3(sin(D3DXToRadian(g_Rotation * 100)), cos(D3DXToRadian(g_Rotation * 100)), cos(D3DXToRadian(g_Rotation * 100)));

	D3DXMatrixIdentity(&g_mtxGWorld);	//���[���h�s���P�ʍs��ɏ�����

	//���]		���[���h�s�� = �X�P�[�����O�s�� * ��]�s�� * ���s�ړ��s��
	//���]		���[���h�s�� = �X�P�[�����O�s�� * ���s�ړ��s�� * ��]�s��

	//�X�P�[���s����쐬&���[���h�s��֍���
	D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&g_mtxGWorld, &g_mtxGWorld, &mtxScl);


	//��]�s����쐬&���[���h�s��֍���
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&g_mtxGWorld, &g_mtxGWorld, &mtxRot);

	//���s�ړ��s����쐬&���[���h�s��֍���
	D3DXMatrixTranslation(&mtxTrs, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&g_mtxGWorld, &g_mtxGWorld, &mtxTrs);


	//���[���h�}�g���b�N�X��ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxGWorld);

	//�`�悵�����|���S���̒��_�o�b�t�@���f�[�^�X�g���[���ɃZ�b�g
	pDevice->SetStreamSource(0, g_pD3DGridBuff, 0, sizeof(VERTEX_3D));

	//�`�悵�����|���S���̒��_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�|���S���̕`��
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, (NumGrid * 8 - 4));
}


void SpriteCube_Draw(D3DXVECTOR3 scl, D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool revolution)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice) return;

	

	//=============================================================
	//������ǉ��@�|���S���̃��[���h�s��̍쐬
	D3DXMATRIX mtxScl;		//�X�P�[�����O�s��
	D3DXMATRIX mtxRot;		//��]�s��
	D3DXMATRIX mtxTrs;		//���s�ړ��s��

	//g_pos = D3DXVECTOR3(sin(D3DXToRadian(g_Rotation * 100)), cos(D3DXToRadian(g_Rotation * 100)), cos(D3DXToRadian(g_Rotation * 100)));

	D3DXMatrixIdentity(&g_mtxWorld);	//���[���h�s���P�ʍs��ɏ�����

	//���]		���[���h�s�� = �X�P�[�����O�s�� * ��]�s�� * ���s�ړ��s��
	//���]		���[���h�s�� = �X�P�[�����O�s�� * ���s�ړ��s�� * ��]�s��

	//�X�P�[���s����쐬&���[���h�s��֍���
	D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxScl);

	if (revolution)
	{
		//���s�ړ��s����쐬&���[���h�s��֍���
		D3DXMatrixTranslation(&mtxTrs, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTrs);

		//��]�s����쐬&���[���h�s��֍���
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxRot);
	}

	else
	{
		//��]�s����쐬&���[���h�s��֍���
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxRot);

		//���s�ړ��s����쐬&���[���h�s��֍���
		D3DXMatrixTranslation(&mtxTrs, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTrs);
	}

	//���[���h�}�g���b�N�X��ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

	//�`�悵�����|���S���̒��_�o�b�t�@���f�[�^�X�g���[���ɃZ�b�g
	pDevice->SetStreamSource(0, g_pD3DVtxBuff, 0, sizeof(VERTEX_3D));

	//�`�悵�����|���S���̒��_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�|���S���̕`��
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_KIZUNA));
	pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 12);
}

// �X�v���C�g�`��
// ���e�N�X�`���؂��蕝�A�����Ɠ����傫���̃X�v���C�g���w����W�ɕ`�悷��
void Sprite_Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty,int tw, int th)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
    if( !pDevice ) return;

	float w = (float)Texture_GetWidth(texture_index);
	float h = (float)Texture_GetHeight(texture_index);

    // UV���W�v�Z
    float u[2], v[2];
	u[0] = (float)tx / w;
	v[0] = (float)ty / h;
	u[1] = (float)(tx + tw) / w;
	v[1] = (float)(ty + th) / h;

    Vertex2D vertexes[] = {
        { D3DXVECTOR4(dx      - 0.5f, dy      - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[0], v[0]) },
        { D3DXVECTOR4(dx + tw - 0.5f, dy      - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[1], v[0]) },
		{ D3DXVECTOR4(dx      - 0.5f, dy + th - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[0], v[1]) },
		{ D3DXVECTOR4(dx + tw - 0.5f, dy + th - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[1], v[1]) },
    };

    pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, Texture_GetTexture(texture_index));
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertexes, sizeof(Vertex2D));
}
