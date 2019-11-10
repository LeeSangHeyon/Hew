
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

//3Dポリゴン頂点フォーマット構造体を定義
typedef struct
{
	D3DXVECTOR3 vtx;	//頂点座標
	D3DXVECTOR3 nor;	//法線ベクトル
	D3DCOLOR diffuse;	//反射光
	D3DXVECTOR2 tex;	//テクスチャ座標
} VERTEX_3D;


//3Dポリゴン頂点フォーマット(頂点座標[3D] / 法線 / 反射光 / テクスチャ座標 )
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#endif // COMMON_H_





