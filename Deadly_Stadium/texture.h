
#ifndef TEXTURE_H_
#define TEXTURE_H_


#include <d3d9.h>


/*------------------------------------------------------------------------------
   �e�N�X�`���񋓌^
------------------------------------------------------------------------------*/
// �e�N�X�`���Ǘ��ԍ�
typedef enum TextureIndex
{
	TEXTURE_INDEX_YELLOW,
    TEXTURE_INDEX_PLAYERICON,
	TEXTURE_INDEX_SKILLHUD,
	TEXTURE_INDEX_BAR,
	TEXTURE_INDEX_UNDERBAR,
	TEXTURE_INDEX_FIELD,
	TEXTURE_INDEX_GRAY,
	TEXTURE_INDEX_BOW,
    TEXTURE_INDEX_FENCING,

	TEXTURE_INDEX_MAX
};


/*------------------------------------------------------------------------------
   �֐��̃v���g�^�C�v�錾
------------------------------------------------------------------------------*/
// �e�N�X�`���̓ǂݍ���
//
// �߂�l:�ǂݍ��߂Ȃ�������
//
int Texture_Load(void);

// �e�N�X�`���̉��
void Texture_Release(void);

// �e�N�X�`���C���^�[�t�F�[�X�̎擾
//
// �߂�l:�e�N�X�`���C���^�[�t�F�[�X
//        ���������݂��Ȃ�index���w�肵���ꍇ�ANULL
LPDIRECT3DTEXTURE9 Texture_GetTexture(TextureIndex index);

// �e�N�X�`���𑜓x���̎擾
//
// ���� ... index �e�N�X�`���Ǘ��ԍ�
//
int Texture_GetWidth(TextureIndex index);

// �e�N�X�`���𑜓x�����̎擾
//
// ���� ... index �e�N�X�`���Ǘ��ԍ�
//
int Texture_GetHeight(TextureIndex index);


#endif // TEXTURE_H_
