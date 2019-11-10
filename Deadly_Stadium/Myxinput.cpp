#include "Myxinput.h"

int GAMEPAD::padCnt;


GAMEPAD::GAMEPAD()
{
	////������
	//bVibration = false;
	//VibrationSetting = { 0xFFFF / 2, 0xFFFF / 2 };


	////�R���g���[����Ԃ��擾�A�ڑ���Ԃ��i�[
	//if (ERROR_SUCCESS == XInputGetState(padCnt, &State))
	//{
	//	OldState.Gamepad = State.Gamepad;
	//	bConnected = true;
	//	Number = padCnt;
	//	padCnt++;
	//}
	//else
	//{
	//	bConnected = false;
	//	State = {};
	//}
}

void GAMEPAD::Init()
{
	//������
	bVibration = false;
	VibrationSetting = { 0xFFFF / 2, 0xFFFF / 2 };


	//�R���g���[����Ԃ��擾�A�ڑ���Ԃ��i�[
	if (ERROR_SUCCESS == XInputGetState(padCnt, &State))
	{
		OldState.Gamepad = State.Gamepad;
		bConnected = true;
		Number = padCnt;
		padCnt++;
	}
	else
	{
		bConnected = false;
		State = {};
	}
}


GAMEPAD::~GAMEPAD()
{
	//�U����~
	VibrationState = { 0,0 };
	XInputSetState(Number, &VibrationState);

	padCnt--;
}

//�����K�����t���[���Ăяo��
void GAMEPAD::Update()
{
	//�P�t���[���O�̏���ۑ�
	OldState.Gamepad = State.Gamepad;

	//��ԍX�V
	if (ERROR_SUCCESS != XInputGetState(Number, &State))
	{
		bConnected = false;
		bVibration = false;
		VibrationState = { 0,0 };
		XInputSetState(Number, &VibrationState);
		State = {};
		return;				//�ڑ��؂�
	}

	
	//--------------�������l�ł̏���-------------------

	if ((State.Gamepad.sThumbLX < STICK_THRESHOLD &&
		State.Gamepad.sThumbLX > -STICK_THRESHOLD) &&
		(State.Gamepad.sThumbLY < STICK_THRESHOLD &&
			State.Gamepad.sThumbLY > -STICK_THRESHOLD))
	{//���X�e�B�b�N
		State.Gamepad.sThumbLX = 0;
		State.Gamepad.sThumbLY = 0;
	}

	if ((State.Gamepad.sThumbRX < STICK_THRESHOLD &&
		State.Gamepad.sThumbRX > -STICK_THRESHOLD) &&
		(State.Gamepad.sThumbRY < STICK_THRESHOLD &&
			State.Gamepad.sThumbRY > -STICK_THRESHOLD))
	{//�E�X�e�B�b�N
		State.Gamepad.sThumbRX = 0;
		State.Gamepad.sThumbRY = 0;
	}

	if (State.Gamepad.bLeftTrigger < STICK_THRESHOLD)
	{//���g���K�[
		State.Gamepad.bLeftTrigger = 0;
	}

	if (State.Gamepad.bRightTrigger < STICK_THRESHOLD)
	{//�E�g���K�[
		State.Gamepad.bRightTrigger = 0;
	}


	if (VibrationFrame <= 0 && bVibration)
	{//�U����~
		bVibration = false;
		VibrationState = { 0,0 };
		XInputSetState(Number, &VibrationState);
	}
	else if( bVibration)
		VibrationFrame--;

}


bool GAMEPAD::GetKeyDown(WORD key)
{
	if (State.Gamepad.wButtons &key) return true;
	else return false;
}

bool GAMEPAD::GetKeyPress(WORD key)
{
	if ((State.Gamepad.wButtons &key) && !(OldState.Gamepad.wButtons &key))
	{
		return true;
	}
	return false;
}

bool GAMEPAD::GetKeyUp(WORD key)
{
	if (!(State.Gamepad.wButtons &key) && (OldState.Gamepad.wButtons &key))
	{
		return true;
	}
	return false;
}

bool GAMEPAD::GetKeyDownAnyKey()
{
	if (State.Gamepad.wButtons)		return true;
	else	return false;
}

//�t���[���P�ʂŐU�����Z�b�g
void GAMEPAD::SetVibration(int Frame)
{
	VibrationFrame = Frame; 
	bVibration = true;
	VibrationState = VibrationSetting;
	XInputSetState(Number, &VibrationState);
}


//�U���̋��x�i0~65534�j�̐ݒ�
//�E�̃��[�^�[�͍����g���[�^�[�ŁA���̃��[�^�[�͒���g���[�^�[�B
void GAMEPAD::SetVibrationStrength(WORD Left, WORD Right)
{
	VibrationSetting.wLeftMotorSpeed = Left;
	VibrationSetting.wRightMotorSpeed = Right;
}
