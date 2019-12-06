
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


#endif // COMMON_H_





