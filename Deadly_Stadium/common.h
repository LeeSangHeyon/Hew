
//==============================================================================*/
#ifndef COMMON_H_
#define COMMON_H_

#include <d3dx9.h>

/*------------------------------------------------------------------------------
   定数定義
------------------------------------------------------------------------------*/
#define SCREEN_WIDTH  (1600) // スクリーン(クライアント領域)の幅
#define SCREEN_HEIGHT  (900) // スクリーン(クライアント領域)の高さ


//プロジェクション用パラメータ
#define VIEW_ANGLE		(D3DXToRadian(45.0f))							//ビュー平面の視野角
#define VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	//ビュー平面のアスペクト比
#define VIEW_NEAR_Z		(1.0f)											//ビュー平面のNearZ値
#define VIEW_FAR_Z		(1000.0f)										//ビュー平面のFarZ値


#endif // COMMON_H_





