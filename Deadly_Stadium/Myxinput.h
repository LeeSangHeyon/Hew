#pragma once
#pragma comment (lib, "xinput.lib")

#include <Windows.h>
#include <Xinput.h>

#define MAX_CONTROLLERS  4  //XInput���F���ł���̂�4�܂�
#define STICK_THRESHOLD   65535/8 //�������l
#define TRIGGER_THRESHOLD   8 //�������l


//�X�e�B�b�N�̏�Ԃ��i�[����
struct Stick
{
	SHORT x, y;
};



class GAMEPAD
{
	//�Q�[���p�b�h�X�e�[�g
	XINPUT_STATE		State;			
	XINPUT_STATE		OldState;
	bool				bConnected;		//�ڑ����Ă邩�ǂ���
	int					Number;				//�p�b�h�̔ԍ�

	//�U��
	XINPUT_VIBRATION	VibrationState, VibrationSetting;
	int					VibrationFrame;		//�U���t���[���� 
	bool				bVibration;		//�U���̏��

	static int			padCnt;				//�Q�[���p�b�h�C���X�^���X�̑���

public:
	GAMEPAD();
	~GAMEPAD();

	void Init();

	//�����K�����t���[���Ăяo��
	void Update();


	//�{�^���̏��擾
	bool GetKeyDown(WORD key);	//�L�[�������Ă��
	bool GetKeyTrigger(WORD key);	//�L�[���������u��
	bool GetKeyRelease(WORD key);	//�L�[�𗣂����u��

	bool GetKeyDownAnyKey();	//�ǂꂩ�����Ă�Ȃ�

	bool GetRightRelease();

	//���E�g���K�[�̎擾(0~255)
	BYTE GetLeftTrigger() { return State.Gamepad.bLeftTrigger; }
	BYTE GetRightTrigger() { return State.Gamepad.bRightTrigger; }

	//�X�e�B�b�N�̎擾()
	Stick GetLeftStick() { return { State.Gamepad.sThumbLX,State.Gamepad.sThumbLY }; }
	Stick GetRightStick() { return { State.Gamepad.sThumbRX,State.Gamepad.sThumbRY }; }



	//�t���[���P�ʂŐU�����Z�b�g
	void SetVibration(int Frame);

	//�U���̋��x�i0~65536�j�̐ݒ�B�E�������g�A��������g�炵���B
	void SetVibrationStrength(WORD Left, WORD Right);


	//�ڑ��󋵂�Ԃ�
	bool GetIsConnected() { return bConnected; }

	//�����̃|�C���^��Ԃ�
	GAMEPAD *ThisPtr() { return this; }
};

