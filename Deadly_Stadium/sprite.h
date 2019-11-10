#ifndef SPRITE_H_
#define SPRITE_H_


#include <d3d9.h>    // D3DCOLOR
#include <d3dx9.h>
#include "texture.h" // TextureIndex


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

#endif // SPRITE_H_
