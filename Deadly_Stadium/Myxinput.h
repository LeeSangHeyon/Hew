#pragma once
#pragma comment (lib, "xinput.lib")

#include <Windows.h>
#include <Xinput.h>

#define MAX_CONTROLLERS  4  //XInputが認識できるのは4つまで
#define STICK_THRESHOLD   65535/8 //しきい値
#define TRIGGER_THRESHOLD   8 //しきい値


//スティックの状態を格納する
struct Stick
{
	SHORT x, y;
};



class GAMEPAD
{
	//ゲームパッドステート
	XINPUT_STATE		State;			
	XINPUT_STATE		OldState;
	bool				bConnected;		//接続してるかどうか
	int					Number;				//パッドの番号

	//振動
	XINPUT_VIBRATION	VibrationState, VibrationSetting;
	int					VibrationFrame;		//振動フレーム数 
	bool				bVibration;		//振動の状態

	static int			padCnt;				//ゲームパッドインスタンスの総数

public:
	GAMEPAD();
	~GAMEPAD();

	void Init();

	//これを必ず毎フレーム呼び出す
	void Update();


	//ボタンの情報取得
	bool GetKeyDown(WORD key);	//キーを押してる間
	bool GetKeyTrigger(WORD key);	//キーを押した瞬間
	bool GetKeyRelease(WORD key);	//キーを離した瞬間

	bool GetKeyDownAnyKey();	//どれか押してるなら

	bool GetRightRelease();

	//左右トリガーの取得(0~255)
	BYTE GetLeftTrigger() { return State.Gamepad.bLeftTrigger; }
	BYTE GetRightTrigger() { return State.Gamepad.bRightTrigger; }

	//スティックの取得()
	Stick GetLeftStick() { return { State.Gamepad.sThumbLX,State.Gamepad.sThumbLY }; }
	Stick GetRightStick() { return { State.Gamepad.sThumbRX,State.Gamepad.sThumbRY }; }



	//フレーム単位で振動をセット
	void SetVibration(int Frame);

	//振動の強度（0~65536）の設定。右が高周波、左が低周波らしい。
	void SetVibrationStrength(WORD Left, WORD Right);


	//接続状況を返す
	bool GetIsConnected() { return bConnected; }

	//自分のポインタを返す
	GAMEPAD *ThisPtr() { return this; }
};

