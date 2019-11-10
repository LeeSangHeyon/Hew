

#ifndef MYDIRECT3D_H_
#define MYDIRECT3D_H_


#include <Windows.h>
#include <d3d9.h>


// Direct3Dの初期化
//
// 戻り値:初期化に失敗したらfalse
//
// 引数:hWnd ... ウィンドウハンドル
//
bool MyDirect3D_Initialize(HWND hWnd);

// Direct3Dの終了処理
void MyDirect3D_Finalize(void);

// Direct3Dデバイスポインタの取得
LPDIRECT3DDEVICE9 MyDirect3D_GetDevice(void);


#endif // MYDIRECT3D_H_