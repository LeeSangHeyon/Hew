
#include <d3dx9.h>
#include <math.h>
#include "mydirect3d.h"
#include "texture.h"
#include "common.h"

#define NumGrid (20)

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


//カメラ用パラメータ
D3DXVECTOR3		g_posCameraEye;			//カメラの視点
D3DXVECTOR3		g_posCameraAt;			//カメラの視点
D3DXVECTOR3		g_vecCameraUp;			//カメラの視点

//プロジェクション&カメラ行列
D3DXMATRIX		g_mtxView;				//ビューマトリックス
D3DXMATRIX		g_mtxProjection;		//プロジェクションマトリックス

//サンプルポリゴンの表示自体に関するパラメータ
D3DXMATRIX		g_mtxWorld;				//ワールドマトリックス
D3DXMATRIX		g_mtxGWorld;				//ワールドマトリックス

LPDIRECT3DVERTEXBUFFER9	g_pD3DVtxBuff;		//頂点バッファ
LPDIRECT3DVERTEXBUFFER9	g_pD3DGridBuff;		//グリッド頂点バッファ


/*------------------------------------------------------------------------------
   グローバル変数宣言
------------------------------------------------------------------------------*/
static D3DCOLOR g_Color = 0xffffffff;
// static D3DCOLOR g_Color = D3DCOLOR_RGBA(255, 255, 255, 255);



/*------------------------------------------------------------------------------
   関数定義
------------------------------------------------------------------------------*/

void Sprite_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	//オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 36,		//頂点データ用に確保するバッファサイズ
		D3DUSAGE_WRITEONLY,		//頂点バッファの使用法
		FVF_VERTEX_3D,			//使用する頂点フォーマット
		D3DPOOL_MANAGED,		//リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuff,			//頂点バッファインターフェースへのポインタ
		NULL);

	//頂点バッファの中身を埋める
	VERTEX_3D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定

	D3DXVECTOR3 Cube[8] =
	{
		D3DXVECTOR3(-0.5f,-0.5f,  0.5f),	//0
		D3DXVECTOR3(0.5f,-0.5f,  0.5f),		//1
		D3DXVECTOR3(-0.5f, 0.5f,  0.5f),	//2
		D3DXVECTOR3(0.5f, 0.5f,  0.5f),		//3
		D3DXVECTOR3(0.5f, 0.5f, -0.5f),		//4
		D3DXVECTOR3(0.5f,-0.5f, -0.5f),		//5
		D3DXVECTOR3(-0.5f,-0.5f, -0.5f),	//6
		D3DXVECTOR3(-0.5f, 0.5f, -0.5f)		//7
	};

	pVtx[0].vtx = pVtx[19].vtx = pVtx[21].vtx = pVtx[26].vtx = pVtx[29].vtx = Cube[0];
	pVtx[1].vtx = pVtx[3].vtx = pVtx[6].vtx = pVtx[28].vtx = Cube[1];
	pVtx[2].vtx = pVtx[5].vtx = pVtx[22].vtx = pVtx[30].vtx = Cube[2];
	pVtx[4].vtx = pVtx[8].vtx = pVtx[11].vtx = pVtx[31].vtx = pVtx[33].vtx = Cube[3];
	pVtx[10].vtx = pVtx[14].vtx = pVtx[17].vtx = pVtx[34].vtx = Cube[4];
	pVtx[7].vtx = pVtx[9].vtx = pVtx[12].vtx = pVtx[25].vtx = pVtx[27].vtx = Cube[5];
	pVtx[13].vtx = pVtx[15].vtx = pVtx[18].vtx = pVtx[24].vtx = Cube[6];
	pVtx[16].vtx = pVtx[20].vtx = pVtx[23].vtx = pVtx[32].vtx = pVtx[35].vtx = Cube[7];


	//法線ベクトルの設定
	for (int i = 0; i < 6; i++)
	{
		pVtx[0 + 6 * i].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1 + 6 * i].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2 + 6 * i].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3 + 6 * i].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[4 + 6 * i].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[5 + 6 * i].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	}


	//反射光の設定
	for (int i = 0; i < 6; i++)
	{
		pVtx[0 + 6 * i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1 + 6 * i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2 + 6 * i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3 + 6 * i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[4 + 6 * i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5 + 6 * i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//テクスチャ座標の設定
	for (int i = 0; i < 6; i++)
	{
		pVtx[0 + 6 * i].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1 + 6 * i].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2 + 6 * i].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3 + 6 * i].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[4 + 6 * i].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[5 + 6 * i].tex = D3DXVECTOR2(0.0f, 1.0f);
	}

	//頂点データをアンロックする
	g_pD3DVtxBuff->Unlock();

	//グリッド頂点座標の設定

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (NumGrid * 8 - 4),		//頂点データ用に確保するバッファサイズ
		D3DUSAGE_WRITEONLY,		//頂点バッファの使用法
		FVF_VERTEX_3D,			//使用する頂点フォーマット
		D3DPOOL_MANAGED,		//リソースのバッファを保持するメモリクラスを指定
		&g_pD3DGridBuff,			//頂点バッファインターフェースへのポインタ
		NULL);

	//頂点バッファの中身を埋める
	VERTEX_3D *pGrid;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pD3DGridBuff->Lock(0, 0, (void**)&pGrid, 0);

	//頂点座標の設定

	pGrid[0].vtx = D3DXVECTOR3(0.0f, 0.0f, NumGrid);
	pGrid[1].vtx = D3DXVECTOR3(0.0f, 0.0f, -NumGrid);
	pGrid[2].vtx = D3DXVECTOR3(NumGrid, 0.0f, 0.0f);
	pGrid[3].vtx = D3DXVECTOR3(-NumGrid, 0.0f, 0.0f);

	for (int i = 1; i < NumGrid; i++)
	{
		pGrid[8 * i - 4].vtx = D3DXVECTOR3(i, 0.0f, NumGrid);
		pGrid[8 * i - 3].vtx = D3DXVECTOR3(i, 0.0f, -NumGrid);
		pGrid[8 * i - 2].vtx = D3DXVECTOR3(NumGrid, 0.0f, i);
		pGrid[8 * i - 1].vtx = D3DXVECTOR3(-NumGrid, 0.0f, i);
		pGrid[8 * i + 0].vtx = D3DXVECTOR3(-i, 0.0f, NumGrid);
		pGrid[8 * i + 1].vtx = D3DXVECTOR3(-i, 0.0f, -NumGrid);
		pGrid[8 * i + 2].vtx = D3DXVECTOR3(NumGrid, 0.0f, -i);
		pGrid[8 * i + 3].vtx = D3DXVECTOR3(-NumGrid, 0.0f, -i);
	}

	for (int i = 0; i < NumGrid * 8 - 4; i++)
	{

		pGrid[i].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pGrid[i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pGrid[i].tex = D3DXVECTOR2(0.0f, 0.0f);

	}

	g_pD3DGridBuff->Unlock();
}

//カメラ
void Camera_Set(void)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice) return;

	g_posCameraEye = D3DXVECTOR3(0, 4.0f, -2.0f);
	g_posCameraAt = D3DXVECTOR3(0, 0, 0);
	g_vecCameraUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//ビュー行列の作成
	D3DXMatrixLookAtLH(&g_mtxView,
		&g_posCameraEye,	//カメラ視点
		&g_posCameraAt,		//カメラ注視点
		&g_vecCameraUp);	//カメラ上方向

	//ビュー行列の設定
	pDevice->SetTransform(D3DTS_VIEW, &g_mtxView);


	//==============================================
	// ここを追加　テスト用プロジェクション行列の作成
	D3DXMatrixPerspectiveFovLH(&g_mtxProjection,
		VIEW_ANGLE,		//ビュー平面の視野角
		VIEW_ASPECT,	//ビュー平面のアスペクト比
		VIEW_NEAR_Z,	//ビュー平面のNearZ
		VIEW_FAR_Z);	//ビュー平面のFarZ

	//プロジェクション行列の設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_mtxProjection);

}

// スプライトポリゴンの頂点カラー設定
void Sprite_SetColor(D3DCOLOR color)
{
	g_Color = color;
}


void Grid_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice) return;

	D3DXVECTOR3 scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 pos = D3DXVECTOR3(0, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0, 0, 0);

	D3DXMATRIX mtxScl;		//スケーリング行列
	D3DXMATRIX mtxRot;		//回転行列
	D3DXMATRIX mtxTrs;		//平行移動行列

	//g_pos = D3DXVECTOR3(sin(D3DXToRadian(g_Rotation * 100)), cos(D3DXToRadian(g_Rotation * 100)), cos(D3DXToRadian(g_Rotation * 100)));

	D3DXMatrixIdentity(&g_mtxGWorld);	//ワールド行列を単位行列に初期化

	//自転		ワールド行列 = スケーリング行列 * 回転行列 * 平行移動行列
	//公転		ワールド行列 = スケーリング行列 * 平行移動行列 * 回転行列

	//スケール行列を作成&ワールド行列へ合成
	D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&g_mtxGWorld, &g_mtxGWorld, &mtxScl);


	//回転行列を作成&ワールド行列へ合成
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&g_mtxGWorld, &g_mtxGWorld, &mtxRot);

	//平行移動行列を作成&ワールド行列へ合成
	D3DXMatrixTranslation(&mtxTrs, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&g_mtxGWorld, &g_mtxGWorld, &mtxTrs);


	//ワールドマトリックスを設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxGWorld);

	//描画したいポリゴンの頂点バッファをデータストリームにセット
	pDevice->SetStreamSource(0, g_pD3DGridBuff, 0, sizeof(VERTEX_3D));

	//描画したいポリゴンの頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ポリゴンの描画
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, (NumGrid * 8 - 4));
}


void SpriteCube_Draw(D3DXVECTOR3 scl, D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool revolution)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice) return;

	

	//=============================================================
	//ここを追加　ポリゴンのワールド行列の作成
	D3DXMATRIX mtxScl;		//スケーリング行列
	D3DXMATRIX mtxRot;		//回転行列
	D3DXMATRIX mtxTrs;		//平行移動行列

	//g_pos = D3DXVECTOR3(sin(D3DXToRadian(g_Rotation * 100)), cos(D3DXToRadian(g_Rotation * 100)), cos(D3DXToRadian(g_Rotation * 100)));

	D3DXMatrixIdentity(&g_mtxWorld);	//ワールド行列を単位行列に初期化

	//自転		ワールド行列 = スケーリング行列 * 回転行列 * 平行移動行列
	//公転		ワールド行列 = スケーリング行列 * 平行移動行列 * 回転行列

	//スケール行列を作成&ワールド行列へ合成
	D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxScl);

	if (revolution)
	{
		//平行移動行列を作成&ワールド行列へ合成
		D3DXMatrixTranslation(&mtxTrs, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTrs);

		//回転行列を作成&ワールド行列へ合成
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxRot);
	}

	else
	{
		//回転行列を作成&ワールド行列へ合成
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxRot);

		//平行移動行列を作成&ワールド行列へ合成
		D3DXMatrixTranslation(&mtxTrs, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&g_mtxWorld, &g_mtxWorld, &mtxTrs);
	}

	//ワールドマトリックスを設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

	//描画したいポリゴンの頂点バッファをデータストリームにセット
	pDevice->SetStreamSource(0, g_pD3DVtxBuff, 0, sizeof(VERTEX_3D));

	//描画したいポリゴンの頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ポリゴンの描画
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_KIZUNA));
	pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 12);
}

// スプライト描画
// ※テクスチャ切り取り幅、高さと同じ大きさのスプライトを指定座標に描画する
void Sprite_Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty,int tw, int th)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
    if( !pDevice ) return;

	float w = (float)Texture_GetWidth(texture_index);
	float h = (float)Texture_GetHeight(texture_index);

    // UV座標計算
    float u[2], v[2];
	u[0] = (float)tx / w;
	v[0] = (float)ty / h;
	u[1] = (float)(tx + tw) / w;
	v[1] = (float)(ty + th) / h;

    Vertex2D vertexes[] = {
        { D3DXVECTOR4(dx      - 0.5f, dy      - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[0], v[0]) },
        { D3DXVECTOR4(dx + tw - 0.5f, dy      - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[1], v[0]) },
		{ D3DXVECTOR4(dx      - 0.5f, dy + th - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[0], v[1]) },
		{ D3DXVECTOR4(dx + tw - 0.5f, dy + th - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[1], v[1]) },
    };

    pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, Texture_GetTexture(texture_index));
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertexes, sizeof(Vertex2D));
}
