#ifndef SPRITE_H_
#define SPRITE_H_


#include <d3d9.h>    // D3DCOLOR
#include <d3dx9.h>
#include "texture.h" // TextureIndex

/*------------------------------------------------------------------------------
   構造体宣言
------------------------------------------------------------------------------*/
// ２Dポリゴン頂点構造体
typedef struct Vertex2D_tag
{
	D3DXVECTOR4 position; // 頂点座標（座標変換済み頂点）
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
} Vertex2D;
#define FVF_VERTEX2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1) // ２Dポリゴン頂点フォーマット

//3Dポリゴン頂点フォーマット(頂点座標[3D] / 法線 / 反射光 / テクスチャ座標 )
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_LINE	(D3DFVF_XYZ | D3DFVF_DIFFUSE)


//3Dポリゴン頂点フォーマット構造体を定義
typedef struct
{
	D3DXVECTOR3 vtx;	//頂点座標
	D3DXVECTOR3 nor;	//法線ベクトル
	D3DCOLOR diffuse;	//反射光
	D3DXVECTOR2 tex;	//テクスチャ座標
} VERTEX_3D;

typedef struct
{
	D3DXVECTOR3 vtx;	//頂点座標
	D3DXCOLOR color;
} VERTEX_LINE;

/*------------------------------------------------------------------------------
   関数のプロトタイプ宣言
------------------------------------------------------------------------------*/

//初期化
void Sprite_Initialize(void);

//カメラ
void Camera_Set(void);

// スプライトポリゴンの頂点カラー設定
// ※4頂点すべてに同じカラーを設定する
//
// 引数 ... color 設定する色
void Sprite_SetColor(D3DCOLOR color);

// スプライト描画
// ※テクスチャ解像度と同じ大きさのスプライトを指定座標に描画する
//
// 引数:texture_index ... テクスチャ管理番号
//      dx            ... 描画座標x
//      dy            ... 描画座標y
void Sprite_Draw(TextureIndex texture_index, float dx, float dy);

// スプライト描画
// ※テクスチャ切り取り幅、高さと同じ大きさのスプライトを指定座標に描画する
//
// 引数:texture_index ... テクスチャ管理番号
//      dx            ... 描画座標x
//      dy            ... 描画座標y
//      tx            ... テクスチャ切り取り座標x
//      ty            ... テクスチャ切り取り座標y
//      tw            ... テクスチャ切り取り幅
//      th            ... テクスチャ切り取り高さ
void Sprite_Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th);

void SpriteA_Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th);

void SpriteB_Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th);

// スプライト描画
// ※テクスチャ切り取り幅、高さと同じ大きさのスプライトを指定座標に配置してスプライトの指定座標を中心に拡大、回転描画する
//
// 引数:texture_index ... テクスチャ管理番号
//      dx            ... 描画座標x
//      dy            ... 描画座標y
//      tx            ... テクスチャ切り取り座標x
//      ty            ... テクスチャ切り取り座標y
//      tw            ... テクスチャ切り取り幅
//      th            ... テクスチャ切り取り高さ
//      cx            ... 中心座標x
//      cy            ... 中心座標y
//      sx            ... 拡大率x方向
//      sy            ... 拡大率y方向
//      rotation      ... 回転角度（ラジアン）
void Sprite_Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th, float cx, float cy, float sx, float sy, float rotation);

void SpriteCube_Draw(D3DXVECTOR3 scl, D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool revolution);

void Grid_Draw(void);

void Line_Draw(D3DXVECTOR3 p, D3DXVECTOR3 r);

#endif // SPRITE_H_
