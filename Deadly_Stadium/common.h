
//==============================================================================*/
#ifndef COMMON_H_
#define COMMON_H_

#include <d3dx9.h>

/*------------------------------------------------------------------------------
   �萔��`
------------------------------------------------------------------------------*/
#define SCREEN_WIDTH  (1600) // �X�N���[��(�N���C�A���g�̈�)�̕�
#define SCREEN_HEIGHT  (900) // �X�N���[��(�N���C�A���g�̈�)�̍���


//�v���W�F�N�V�����p�p�����[�^
#define VIEW_ANGLE		(D3DXToRadian(45.0f))							//�r���[���ʂ̎���p
#define VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	//�r���[���ʂ̃A�X�y�N�g��
#define VIEW_NEAR_Z		(1.0f)											//�r���[���ʂ�NearZ�l
#define VIEW_FAR_Z		(1000.0f)										//�r���[���ʂ�FarZ�l

//3D�|���S�����_�t�H�[�}�b�g�\���̂��`
typedef struct
{
	D3DXVECTOR3 vtx;	//���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR diffuse;	//���ˌ�
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
} VERTEX_3D;


//3D�|���S�����_�t�H�[�}�b�g(���_���W[3D] / �@�� / ���ˌ� / �e�N�X�`�����W )
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#endif // COMMON_H_





