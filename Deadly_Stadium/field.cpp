#include <d3dx9.h>
#include <math.h>
#include "mydirect3d.h"
#include "texture.h"
#include "common.h"
#include "debug_printf.h"
#include "sprite.h"


//背景バッファ

LPDIRECT3DVERTEXBUFFER9	g_FieldVtxBuff;		//頂点バッファ
LPDIRECT3DINDEXBUFFER9	g_FieldIdxBuff;		//インデックスバッファ

D3DXMATRIX		g_mtxFWorld;				//ワールドマトリックス

int				g_pNum;

/*------------------------------------------------------------------------------
   関数定義
------------------------------------------------------------------------------*/

void Field_Initialize(float tw, float th, int fx, int fy)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	//背景


	int Ground_N = (fx + 1) * (fy + 1);

	int stripN = 2 * (fx + 2) * fy - 2;

	g_pNum = 2 * (fx + 2) * fy - 4;

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * Ground_N,		//頂点データ用に確保するバッファサイズ
		D3DUSAGE_WRITEONLY,		//頂点バッファの使用法
		FVF_VERTEX_3D,			//使用する頂点フォーマット
		D3DPOOL_MANAGED,		//リソースのバッファを保持するメモリクラスを指定
		&g_FieldVtxBuff,			//頂点バッファインターフェースへのポインタ
		NULL);

	//頂点バッファの中身を埋める
	VERTEX_3D *GVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_FieldVtxBuff->Lock(0, 0, (void**)&GVtx, 0);

	//頂点座標の設定
	float mid_x = fx / 2;
	float mid_y = fy / 2;

	for (int i = 0; i < fy + 1; i++)
	{
		for (int j = 0; j < fx + 1; j++)
		{
			GVtx[i * (fx + 1) + j].vtx = D3DXVECTOR3((j - mid_x) * tw, 0, (i - mid_y) * th);
		}
	}


	//法線ベクトルの設定
	for (int i = 0; i < Ground_N; i++)
	{
		GVtx[i].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	}


	//反射光の設定
	for (int i = 0; i < Ground_N; i++)
	{
		GVtx[i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	}

	//テクスチャ座標の設定
	for (int i = 0; i < fy + 1; i++)
	{
		for (int j = 0; j < fx + 1; j++)
		{
			int Tx = 0, Ty = 0;
			if (j % 2)
				Tx = 1;
			if (i % 2)
				Ty = 1;
			GVtx[i * (fx + 1) + j].tex = D3DXVECTOR2(Tx, Ty);
		}

	}



	//頂点データをアンロックする
	g_FieldVtxBuff->Unlock();


	//インデックスバッファ初期化
	pDevice->CreateIndexBuffer(sizeof(WORD) * stripN,		//頂点データ用に確保するバッファサイズ
		D3DUSAGE_WRITEONLY,		//頂点バッファの使用法
		D3DFMT_INDEX16,			//使用する頂点フォーマット
		D3DPOOL_MANAGED,		//リソースのバッファを保持するメモリクラスを指定
		&g_FieldIdxBuff,			//頂点バッファインターフェースへのポインタ
		NULL);

	//インデックスバッファの中身を埋める
	WORD*	GIdx;

	g_FieldIdxBuff->Lock(0, 0, (void**)&GIdx, 0);

	for (int i = 0; i < fy; i++)
	{
		if (i > 0)
		{
			//JUMP
			GIdx[(i * (fx + 2)) * 2 - 2] = i * (fx + 1) + fx;
			GIdx[(i * (fx + 2)) * 2 - 1] = i * (fx + 1);
		}
		//STRIP
		for (int j = 0; j < fx + 1; j++)
		{
			GIdx[(i * (fx + 2) + j) * 2 + 0] = (i + 0) * (fx + 1) + j;
			GIdx[(i * (fx + 2) + j) * 2 + 1] = (i + 1) * (fx + 1) + j;
		}

	}

	g_FieldIdxBuff->Unlock();
}

void Field_Draw()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice) return;

	D3DXVECTOR3 scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 pos = D3DXVECTOR3(0, -0.5f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0, 0, 0);

	D3DXMATRIX mtxScl;		//スケーリング行列
	D3DXMATRIX mtxRot;		//回転行列
	D3DXMATRIX mtxTrs;		//平行移動行列

	//g_pos = D3DXVECTOR3(sin(D3DXToRadian(g_Rotation * 100)), cos(D3DXToRadian(g_Rotation * 100)), cos(D3DXToRadian(g_Rotation * 100)));

	D3DXMatrixIdentity(&g_mtxFWorld);	//ワールド行列を単位行列に初期化

	//自転		ワールド行列 = スケーリング行列 * 回転行列 * 平行移動行列
	//公転		ワールド行列 = スケーリング行列 * 平行移動行列 * 回転行列

	//スケール行列を作成&ワールド行列へ合成
	D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&g_mtxFWorld, &g_mtxFWorld, &mtxScl);


	//回転行列を作成&ワールド行列へ合成
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&g_mtxFWorld, &g_mtxFWorld, &mtxRot);

	//平行移動行列を作成&ワールド行列へ合成
	D3DXMatrixTranslation(&mtxTrs, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&g_mtxFWorld, &g_mtxFWorld, &mtxTrs);

	//ワールドマトリックスを設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxFWorld);

	//描画したいポリゴンの頂点バッファをデータストリームにセット
	pDevice->SetStreamSource(0, g_FieldVtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetIndices(g_FieldIdxBuff);

	//描画したいポリゴンの頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_FIELD));
	//pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 12);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		0,
		0,
		g_pNum);

	//g_pos = D3DXVECTOR3(sin(D3DXToRadian(g_Rotation * 100)), cos(D3DXToRadian(g_Rotation * 100)), cos(D3DXToRadian(g_Rotation * 100)));

	D3DXMatrixIdentity(&g_mtxFWorld);	//ワールド行列を単位行列に初期化

	//自転		ワールド行列 = スケーリング行列 * 回転行列 * 平行移動行列
	//公転		ワールド行列 = スケーリング行列 * 平行移動行列 * 回転行列

	//スケール行列を作成&ワールド行列へ合成
	D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&g_mtxFWorld, &g_mtxFWorld, &mtxScl);


	//回転行列を作成&ワールド行列へ合成
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&g_mtxFWorld, &g_mtxFWorld, &mtxRot);

	//平行移動行列を作成&ワールド行列へ合成
	D3DXMatrixTranslation(&mtxTrs, pos.x, pos.y + 0.02, pos.z - 13);
	D3DXMatrixMultiply(&g_mtxFWorld, &g_mtxFWorld, &mtxTrs);

	//ワールドマトリックスを設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxFWorld);

	//描画したいポリゴンの頂点バッファをデータストリームにセット
	pDevice->SetStreamSource(0, g_FieldVtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetIndices(g_FieldIdxBuff);

	//描画したいポリゴンの頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_GRAY));
	//pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 12);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		0,
		0,
		g_pNum);

}