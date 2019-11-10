#include "Myxinput.h"

int GAMEPAD::padCnt;


GAMEPAD::GAMEPAD()
{
	////初期化
	//bVibration = false;
	//VibrationSetting = { 0xFFFF / 2, 0xFFFF / 2 };


	////コントローラ状態を取得、接続状態を格納
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
	//初期化
	bVibration = false;
	VibrationSetting = { 0xFFFF / 2, 0xFFFF / 2 };


	//コントローラ状態を取得、接続状態を格納
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
	//振動停止
	VibrationState = { 0,0 };
	XInputSetState(Number, &VibrationState);

	padCnt--;
}

//これを必ず毎フレーム呼び出す
void GAMEPAD::Update()
{
	//１フレーム前の情報を保存
	OldState.Gamepad = State.Gamepad;

	//状態更新
	if (ERROR_SUCCESS != XInputGetState(Number, &State))
	{
		bConnected = false;
		bVibration = false;
		VibrationState = { 0,0 };
		XInputSetState(Number, &VibrationState);
		State = {};
		return;				//接続切れ
	}

	
	//--------------しきい値での処理-------------------

	if ((State.Gamepad.sThumbLX < STICK_THRESHOLD &&
		State.Gamepad.sThumbLX > -STICK_THRESHOLD) &&
		(State.Gamepad.sThumbLY < STICK_THRESHOLD &&
			State.Gamepad.sThumbLY > -STICK_THRESHOLD))
	{//左スティック
		State.Gamepad.sThumbLX = 0;
		State.Gamepad.sThumbLY = 0;
	}

	if ((State.Gamepad.sThumbRX < STICK_THRESHOLD &&
		State.Gamepad.sThumbRX > -STICK_THRESHOLD) &&
		(State.Gamepad.sThumbRY < STICK_THRESHOLD &&
			State.Gamepad.sThumbRY > -STICK_THRESHOLD))
	{//右スティック
		State.Gamepad.sThumbRX = 0;
		State.Gamepad.sThumbRY = 0;
	}

	if (State.Gamepad.bLeftTrigger < STICK_THRESHOLD)
	{//左トリガー
		State.Gamepad.bLeftTrigger = 0;
	}

	if (State.Gamepad.bRightTrigger < STICK_THRESHOLD)
	{//右トリガー
		State.Gamepad.bRightTrigger = 0;
	}


	if (VibrationFrame <= 0 && bVibration)
	{//振動停止
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

//フレーム単位で振動をセット
void GAMEPAD::SetVibration(int Frame)
{
	VibrationFrame = Frame; 
	bVibration = true;
	VibrationState = VibrationSetting;
	XInputSetState(Number, &VibrationState);
}


//振動の強度（0~65534）の設定
//右のモーターは高周波モーターで、左のモーターは低周波モーター。
void GAMEPAD::SetVibrationStrength(WORD Left, WORD Right)
{
	VibrationSetting.wLeftMotorSpeed = Left;
	VibrationSetting.wRightMotorSpeed = Right;
}
