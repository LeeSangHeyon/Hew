

#ifndef MYDIRECT3D_H_
#define MYDIRECT3D_H_


#include <Windows.h>
#include <d3d9.h>


// Direct3D�̏�����
//
// �߂�l:�������Ɏ��s������false
//
// ����:hWnd ... �E�B���h�E�n���h��
//
bool MyDirect3D_Initialize(HWND hWnd);

// Direct3D�̏I������
void MyDirect3D_Finalize(void);

// Direct3D�f�o�C�X�|�C���^�̎擾
LPDIRECT3DDEVICE9 MyDirect3D_GetDevice(void);


#endif // MYDIRECT3D_H_