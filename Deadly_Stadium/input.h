/*==============================================================================
   ※パッド対応はxinputの利用を推奨
==============================================================================*/
#ifndef INPUT_H_
#define INPUT_H_


#include <Windows.h>
// dinput.hをインクルードする前にこれを入れないと警告が出るので注意
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include <Xinput.h>


/*------------------------------------------------------------------------------
   関数のプロトタイプ宣言
------------------------------------------------------------------------------*/

// キーボード入力モジュールの初期化    mainの初期化で呼ぶ
//
// 戻り値：初期化出来なかった場合false
//
// 引数：hinstance ... インスタンスハンドル（WinMainの引数などで取得）
//       hWnd      ... ウィンドウハンドル
//
bool Keyboard_Initialize(HINSTANCE hInstance, HWND hWnd);



// キーボードモジュールの終了処理　　mainの終了処理で呼ぶ
void Keyboard_Finalize(void);


// キーボードモジュールの更新        mainの更新処理の一番最初で呼ぶ（１ループに１回）
// ※キーボード全体のキー状態の取得
//
void Keyboard_Update(void);


// キーボードのキー状態の取得　　　各シーンからキーをチェックをしたいときに呼ぶ
//
// Keyboard_Update()で取得したキーの状態を確認する関数群
//
// 戻り値：指定のキーが
//     Press   ... 押されている
//     Trigger ... 押した瞬間
//     Release ... 離した瞬間
// であった場合trueを返す
//
// 引数：nKey ... 調べたいキーのコード（DIK_～というキー列挙）<------dinput.hを見れ！
//
bool Keyboard_IsPress(int nKey);
bool Keyboard_IsTrigger(int nKey);
bool Keyboard_IsRelease(int nKey);

#endif