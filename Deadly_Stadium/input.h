/*==============================================================================
   ���p�b�h�Ή���xinput�̗��p�𐄏�
==============================================================================*/
#ifndef INPUT_H_
#define INPUT_H_


#include <Windows.h>
// dinput.h���C���N���[�h����O�ɂ�������Ȃ��ƌx�����o��̂Œ���
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include <Xinput.h>


/*------------------------------------------------------------------------------
   �֐��̃v���g�^�C�v�錾
------------------------------------------------------------------------------*/

// �L�[�{�[�h���̓��W���[���̏�����    main�̏������ŌĂ�
//
// �߂�l�F�������o���Ȃ������ꍇfalse
//
// �����Fhinstance ... �C���X�^���X�n���h���iWinMain�̈����ȂǂŎ擾�j
//       hWnd      ... �E�B���h�E�n���h��
//
bool Keyboard_Initialize(HINSTANCE hInstance, HWND hWnd);



// �L�[�{�[�h���W���[���̏I�������@�@main�̏I�������ŌĂ�
void Keyboard_Finalize(void);


// �L�[�{�[�h���W���[���̍X�V        main�̍X�V�����̈�ԍŏ��ŌĂԁi�P���[�v�ɂP��j
// ���L�[�{�[�h�S�̂̃L�[��Ԃ̎擾
//
void Keyboard_Update(void);


// �L�[�{�[�h�̃L�[��Ԃ̎擾�@�@�@�e�V�[������L�[���`�F�b�N���������Ƃ��ɌĂ�
//
// Keyboard_Update()�Ŏ擾�����L�[�̏�Ԃ��m�F����֐��Q
//
// �߂�l�F�w��̃L�[��
//     Press   ... ������Ă���
//     Trigger ... �������u��
//     Release ... �������u��
// �ł������ꍇtrue��Ԃ�
//
// �����FnKey ... ���ׂ����L�[�̃R�[�h�iDIK_�`�Ƃ����L�[�񋓁j<------dinput.h������I
//
bool Keyboard_IsPress(int nKey);
bool Keyboard_IsTrigger(int nKey);
bool Keyboard_IsRelease(int nKey);

#endif