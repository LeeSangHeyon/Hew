
#ifndef TEXTURE_H_
#define TEXTURE_H_


#include <d3d9.h>


/*------------------------------------------------------------------------------
   テクスチャ列挙型
------------------------------------------------------------------------------*/
// テクスチャ管理番号
typedef enum TextureIndex
{
	TEXTURE_INDEX_YELLOW,
    TEXTURE_INDEX_PLAYERICON,
	TEXTURE_INDEX_SKILLHUD,
	TEXTURE_INDEX_BAR,
	TEXTURE_INDEX_UNDERBAR,
	TEXTURE_INDEX_FIELD,
	TEXTURE_INDEX_GRAY,
	TEXTURE_INDEX_BOW,
    TEXTURE_INDEX_FENCING,

	TEXTURE_INDEX_MAX
};


/*------------------------------------------------------------------------------
   関数のプロトタイプ宣言
------------------------------------------------------------------------------*/
// テクスチャの読み込み
//
// 戻り値:読み込めなかった数
//
int Texture_Load(void);

// テクスチャの解放
void Texture_Release(void);

// テクスチャインターフェースの取得
//
// 戻り値:テクスチャインターフェース
//        ただし存在しないindexを指定した場合、NULL
LPDIRECT3DTEXTURE9 Texture_GetTexture(TextureIndex index);

// テクスチャ解像度幅の取得
//
// 引数 ... index テクスチャ管理番号
//
int Texture_GetWidth(TextureIndex index);

// テクスチャ解像度高さの取得
//
// 引数 ... index テクスチャ管理番号
//
int Texture_GetHeight(TextureIndex index);


#endif // TEXTURE_H_
