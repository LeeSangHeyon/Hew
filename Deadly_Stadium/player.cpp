#include <d3dx9.h>
#include <math.h>
#include "mydirect3d.h"
#include "texture.h"
#include "sprite.h"
#include "common.h"
#include "input.h"
#include "Myxinput.h"
#include "camera.h"
#include "player.h"

PLAYER::PLAYER()
{
	pos = D3DXVECTOR3(0.0f, 0.2f, 0.0f);
	rot = D3DXVECTOR3(0, 0, 0);
	scl = D3DXVECTOR3(0.08f, 0.32f, 0.06f);

}


void PLAYER::Init()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	//オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 36,		//頂点データ用に確保するバッファサイズ
		D3DUSAGE_WRITEONLY,		//頂点バッファの使用法
		FVF_VERTEX_3D,			//使用する頂点フォーマット
		D3DPOOL_MANAGED,		//リソースのバッファを保持するメモリクラスを指定
		&pD3DVtxBuff,			//頂点バッファインターフェースへのポインタ
		NULL);

	//頂点バッファの中身を埋める
	VERTEX_3D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

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
		pVtx[1 + 6 * i].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2 + 6 * i].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[3 + 6 * i].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[4 + 6 * i].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[5 + 6 * i].tex = D3DXVECTOR2(0.0f, 0.0f);
	}

	//頂点データをアンロックする
	pD3DVtxBuff->Unlock();

}


void PLAYER::Draw()
{

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice) return;

	D3DXMatrixIdentity(&mtxWorld);	//ワールド行列を単位行列に初期化


	//スケール行列を作成&ワールド行列へ合成
	D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	//回転行列を作成&ワールド行列へ合成
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	//平行移動行列を作成&ワールド行列へ合成
	D3DXMatrixTranslation(&mtxTrs, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrs);


	//ワールドマトリックスを設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//描画したいポリゴンの頂点バッファをデータストリームにセット
	pDevice->SetStreamSource(0, pD3DVtxBuff, 0, sizeof(VERTEX_3D));

	//描画したいポリゴンの頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ポリゴンの描画
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_KIZUNA));
	pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 12);

}


D3DXVECTOR3 PLAYER::GetPos()
{
	return pos;
}


PLAYER_A::PLAYER_A()
{
	pos = D3DXVECTOR3(-0.5f, 0.4f, 0.0f);
	rot = D3DXVECTOR3(0, 0, 0);
	scl = D3DXVECTOR3(0.3f, 0.8f, 0.2f);
}

void PLAYER_A::Update(GAMEPAD pad)
{

	if (Keyboard_IsPress(DIK_W))
	{
		pos.z += speed / 60.0f;
	}
	if (Keyboard_IsPress(DIK_S))
	{
		pos.z -= speed / 60.0f;
	}
	if (Keyboard_IsPress(DIK_D))
	{
		pos.x += speed / 60.0f;
	}
	if (Keyboard_IsPress(DIK_A))
	{
		pos.x -= speed / 60.0f;
	}

	//左スティックの取得
	Stick Lstick = pad.GetLeftStick();

	if (Lstick.x || Lstick.y)
	{
		pos.x += Lstick.x / hypotf(Lstick.x, Lstick.y) * speed / 60.0f;
		pos.z += Lstick.y / hypotf(Lstick.x, Lstick.y) * speed / 60.0f;
	}

	//右スティックの取得
	Stick Rstick = pad.GetRightStick();

	if (Rstick.x || Rstick.y)
	{
		rot.y = (Rstick.y > 0) ? asinf(Rstick.x / hypotf(Rstick.x, Rstick.y)) : -asinf(Rstick.x / hypotf(Rstick.x, Rstick.y));
	}

}

PLAYER_B::PLAYER_B()
{
	pos = D3DXVECTOR3(0.5f, 0.4f, 0.0f);
	rot = D3DXVECTOR3(0, 0, 0);
	scl = D3DXVECTOR3(0.3f, 0.8f, 0.2f);
}

void PLAYER_B::Update(GAMEPAD pad)
{

	if (Keyboard_IsPress(DIK_UP))
	{
		pos.z += speed / 60.0f;
	}
	if (Keyboard_IsPress(DIK_DOWN))
	{
		pos.z -= speed / 60.0f;
	}
	if (Keyboard_IsPress(DIK_RIGHT))
	{
		pos.x += speed / 60.0f;
	}
	if (Keyboard_IsPress(DIK_LEFT))
	{
		pos.x -= speed / 60.0f;
	}

	//左スティックの取得
	Stick Lstick = pad.GetLeftStick();
	if (Lstick.x || Lstick.y)
	{
		pos.x += Lstick.x / hypotf(Lstick.x, Lstick.y) * speed / 60.0f;
		pos.z += Lstick.y / hypotf(Lstick.x, Lstick.y) * speed / 60.0f;
	}

	//右スティックの取得
	Stick Rstick = pad.GetRightStick();

	if (Rstick.x || Rstick.y)
	{
		rot.y = (Rstick.y > 0) ? asinf(Rstick.x / hypotf(Rstick.x, Rstick.y)) : -asinf(Rstick.x / hypotf(Rstick.x, Rstick.y));
	}

}