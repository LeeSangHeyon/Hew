#ifndef SPRITE_H_
#define SPRITE_H_


#include <d3d9.h>    // D3DCOLOR
#include <d3dx9.h>
#include "texture.h" // TextureIndex

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

//3D�|���S�����_�t�H�[�}�b�g(���_���W[3D] / �@�� / ���ˌ� / �e�N�X�`�����W )
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_LINE	(D3DFVF_XYZ | D3DFVF_DIFFUSE)


//3D�|���S�����_�t�H�[�}�b�g�\���̂��`
typedef struct
{
	D3DXVECTOR3 vtx;	//���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR diffuse;	//���ˌ�
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
} VERTEX_3D;

typedef struct
{
	D3DXVECTOR3 vtx;	//���_���W
	D3DXCOLOR color;
} VERTEX_LINE;

/*------------------------------------------------------------------------------
   �֐��̃v���g�^�C�v�錾
------------------------------------------------------------------------------*/

//������
void Sprite_Initialize(void);

//�J����
void Camera_Set(void);

// �X�v���C�g�|���S���̒��_�J���[�ݒ�
// ��4���_���ׂĂɓ����J���[��ݒ肷��
//
// ���� ... color �ݒ肷��F
void Sprite_SetColor(D3DCOLOR color);

// �X�v���C�g�`��
// ���e�N�X�`���𑜓x�Ɠ����傫���̃X�v���C�g���w����W�ɕ`�悷��
//
// ����:texture_index ... �e�N�X�`���Ǘ��ԍ�
//      dx            ... �`����Wx
//      dy            ... �`����Wy
void Sprite_Draw(TextureIndex texture_index, float dx, float dy);

// �X�v���C�g�`��
// ���e�N�X�`���؂��蕝�A�����Ɠ����傫���̃X�v���C�g���w����W�ɕ`�悷��
//
// ����:texture_index ... �e�N�X�`���Ǘ��ԍ�
//      dx            ... �`����Wx
//      dy            ... �`����Wy
//      tx            ... �e�N�X�`���؂�����Wx
//      ty            ... �e�N�X�`���؂�����Wy
//      tw            ... �e�N�X�`���؂��蕝
//      th            ... �e�N�X�`���؂��荂��
void Sprite_Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th);

void SpriteA_Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th);

void SpriteB_Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th);

// �X�v���C�g�`��
// ���e�N�X�`���؂��蕝�A�����Ɠ����傫���̃X�v���C�g���w����W�ɔz�u���ăX�v���C�g�̎w����W�𒆐S�Ɋg��A��]�`�悷��
//
// ����:texture_index ... �e�N�X�`���Ǘ��ԍ�
//      dx            ... �`����Wx
//      dy            ... �`����Wy
//      tx            ... �e�N�X�`���؂�����Wx
//      ty            ... �e�N�X�`���؂�����Wy
//      tw            ... �e�N�X�`���؂��蕝
//      th            ... �e�N�X�`���؂��荂��
//      cx            ... ���S���Wx
//      cy            ... ���S���Wy
//      sx            ... �g�嗦x����
//      sy            ... �g�嗦y����
//      rotation      ... ��]�p�x�i���W�A���j
void Sprite_Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th, float cx, float cy, float sx, float sy, float rotation);

void SpriteCube_Draw(D3DXVECTOR3 scl, D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool revolution);

void Grid_Draw(void);

void Line_Draw(D3DXVECTOR3 p, D3DXVECTOR3 r);

#endif // SPRITE_H_
