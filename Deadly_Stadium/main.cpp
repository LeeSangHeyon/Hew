/*================================

	�Q�[��:	DEADLY STADIUM
	�`�[��: �K��GROUP

	�X�V��:	11/05
	Version 0.1��

=================================*/

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")

#include <Windows.h>
#include "common.h"
#include "mydirect3d.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "Myxinput.h"
#include <d3dx9.h>

#include "camera.h"
#include "player.h"

CAMERA camera;

PLAYER_A player1;

PLAYER_B player2;

GAMEPAD pad1;
GAMEPAD pad2;


/*------------------------------------------------------------------------------
   �萔��`
------------------------------------------------------------------------------*/
#define CLASS_NAME     "GameWindow"       // �E�C���h�E�N���X�̖��O
#define WINDOW_CAPTION "�Q�[���E�B���h�E" // �E�B���h�E�̖��O


/*------------------------------------------------------------------------------
   �v���g�^�C�v�錾
------------------------------------------------------------------------------*/
// �E�B���h�E�v���V�[�W��(�R�[���o�b�N�֐�)
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// �Q�[���̏������֐�
// �߂�l:�������Ɏ��s�����Ƃ�false
static bool Initialize(void);
// �Q�[���̍X�V�֐�
static void Update(void);
// �Q�[���̕`��֐�
static void Draw(void);
// �Q�[���̏I������
static void Finalize(void);


/*------------------------------------------------------------------------------
   �O���[�o���ϐ��錾
------------------------------------------------------------------------------*/
static HWND g_hWnd;             // �E�B���h�E�n���h��
static float g_Rotation = 0.0f; // �X�v���C�g��]�p�x 

/*------------------------------------------------------------------------------
   �֐���`
------------------------------------------------------------------------------*/

//#######################################################################
// ���C���֐�
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // �g�p���Ȃ��ꎞ�ϐ��𖾎�
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // �E�B���h�E�N���X�\���̂̐ݒ�
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;                          // �E�B���h�E�v���V�[�W���̎w��
    wc.lpszClassName = CLASS_NAME;                     // �N���X���̐ݒ�
    wc.hInstance = hInstance;                          // �C���X�^���X�n���h���̎w��
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);          // �}�E�X�J�[�\�����w��
    wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1); // �E�C���h�E�̃N���C�A���g�̈�̔w�i�F��ݒ�

    // �N���X�o�^
    RegisterClass(&wc);


    // �E�B���h�E�X�^�C��
    //DWORD window_style = WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME);
	DWORD window_style = (WS_VISIBLE | WS_POPUP);

    // ��{��`���W
    RECT window_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    // �w�肵���N���C�A���g�̈���m�ۂ��邽�߂ɐV���ȋ�`���W���v�Z
    AdjustWindowRect(&window_rect, window_style, FALSE);

    // �V����Window�̋�`���W���畝�ƍ������Z�o
    int window_width = window_rect.right - window_rect.left;
    int window_height = window_rect.bottom - window_rect.top;

    // �v���C�}�����j�^�[�̉�ʉ𑜓x�擾
    int desktop_width = GetSystemMetrics(SM_CXSCREEN);
    int desktop_height = GetSystemMetrics(SM_CYSCREEN);

    // �f�X�N�g�b�v�̐^�񒆂ɃE�B���h�E�����������悤�ɍ��W���v�Z
    // ��������������A�f�X�N�g�b�v���E�B���h�E���傫���ꍇ�͍���ɕ\��
    int window_x = max((desktop_width - window_width) / 2, 0);
    int window_y = max((desktop_height - window_height) / 2, 0);

    // �E�B���h�E�̐���
    g_hWnd = CreateWindow(
        CLASS_NAME,     // �E�B���h�E�N���X
        WINDOW_CAPTION, // �E�B���h�E�e�L�X�g
        window_style,   // �E�B���h�E�X�^�C��
        window_x,       // �E�B���h�E���Wx
        window_y,       // �E�B���h�E���Wy
        window_width,   // �E�B���h�E�̕�
        window_height,  // �E�B���h�E�̍���
        NULL,           // �e�E�B���h�E�n���h��
        NULL,           // ���j���[�n���h��
        hInstance,      // �C���X�^���X�n���h��
        NULL            // �ǉ��̃A�v���P�[�V�����f�[�^
    );

    if( g_hWnd == NULL ) {
        // �E�B���h�E�n���h�������炩�̗��R�Ő����o���Ȃ�����
        return -1;
    }

	Keyboard_Initialize(hInstance, g_hWnd);

    // �w��̃E�B���h�E�n���h���̃E�B���h�E���w��̕��@�ŕ\��
    ShowWindow(g_hWnd, nCmdShow);


	// �Q�[���̏�����(Direct3D�̏�����)
	if( !Initialize() ) {
        // �Q�[���̏������Ɏ��s����
		return -1;
	}

    // Windows�Q�[���p���C�����[�v
    MSG msg = {}; // msg.message == WM_NULL
    while( WM_QUIT != msg.message ) {

        if( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) ) {
            // ���b�Z�[�W������ꍇ�̓��b�Z�[�W������D��
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            // �Q�[���̍X�V
			Keyboard_Update();
			pad1.Update();
			pad2.Update();
			Update();
			// �Q�[���̕`��
			Draw();
        }
    }

	// �Q�[���̏I������(Direct3D�̏I������)
	Keyboard_Finalize();
	Finalize();

    return (int)msg.wParam;
}

//#######################################################################
// �E�B���h�E�v���V�[�W��(�R�[���o�b�N�֐�)
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch( uMsg ) {
        case WM_KEYDOWN:
            if( wParam == VK_ESCAPE ) {
                SendMessage(hWnd, WM_CLOSE, 0, 0); // WM_CLOSE���b�Z�[�W�̑��M
            }
            break;

        case WM_CLOSE:
            if( MessageBox(hWnd, "�{���ɏI�����Ă�낵���ł����H", "�m�F", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK ) {
                DestroyWindow(hWnd); // �w��̃E�B���h�E��WM_DESTROY���b�Z�[�W�𑗂�
            }
            return 0; // DefWindowProc�֐��Ƀ��b�Z�[�W�𗬂����I�����邱�Ƃɂ���ĉ����Ȃ��������Ƃɂ���

        case WM_DESTROY: // �E�B���h�E�̔j�����b�Z�[�W
            PostQuitMessage(0); // WM_QUIT���b�Z�[�W�̑��M
            return 0;
    };

    // �ʏ탁�b�Z�[�W�����͂��̊֐��ɔC����
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


//#######################################################################
// �Q�[���̏������֐�
bool Initialize(void)
{
    // Direct3D���b�p�[���W���[���̏�����
    if( !MyDirect3D_Initialize(g_hWnd) ) {
        return false;
    }

    // �e�N�X�`���̓ǂݍ���
    if( Texture_Load() > 0 ) {
        MessageBox(g_hWnd, "�������ǂݍ��߂Ȃ������e�N�X�`���t�@�C��������܂�", "�G���[", MB_OK);
    }

	Sprite_Initialize();

	player1.Init();

	player2.Init();

	pad1.Init();

	pad2.Init();

    return true;
}

//#######################################################################
// �Q�[���̍X�V�֐�
void Update(void)
{
	player1.Update(pad1);
	player2.Update(pad2);
	camera.GetPlayerPos(player1.GetPos(), player2.GetPos());
	camera.Update();
    g_Rotation += 0.01f;	//�K���Ɋp�x�̑����𑝂₷
}

//#######################################################################
// �Q�[���̕`��֐�
void Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice) return;

    // ��ʂ̃N���A
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(10, 40, 20, 255), 1.0f, 0);

    // �`��o�b�`���߂̊J�n
	pDevice->BeginScene();

	camera.Set();

	Grid_Draw();

	player1.Draw();

	player2.Draw();


    // �`��o�b�`���߂̏I��
	pDevice->EndScene();

    // �o�b�N�o�b�t�@���t���b�v�i�^�C�~���O��D3DPRESENT_PARAMETERS�̐ݒ�ɂ��j
	pDevice->Present(NULL, NULL, NULL, NULL);
}

//#######################################################################
// �Q�[���̏I������
void Finalize(void)
{
    // �e�N�X�`���̉��
    Texture_Release();

    // Direct3D���b�p�[���W���[���̏I������
    MyDirect3D_Finalize();




}
